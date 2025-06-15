// 15 вариант ЦУиМ 4 лаб. работа
// f(x) = ln(|cos(x) + sin(x)|)      <-- функция C
// yi = f(xi) | i = 1, n             <-- функция asm


/*
    Для работы с прогой:
    Ставим break point на: 
    61 - точка перед вызовом функции masm
    63 - точка после вызова функции masm
    131 - точка перед вызовом функции python
    132 - точка после выова функции python
    Отладка --> окна --> показать средства диагностики --> события
    смотрим на столбец "длительность"
    где видим, после прохождения точек длительность выполнения кода до ее вызова и после
*/





// Доп задание:
// необходимо проанализировать, на сколько машинных циклов код в masm быстре, чем код python
// Убейте меня 

#include <iostream>
#include <string>
#include <vector> // не нужна
#include <Windows.h>
#include <Python.h>
#include "c_func.c"
#include <locale.h>
//#include "py_code.py"

//using namespace std;
extern "C" void func1(float* massive, int n); // функция в asm , которую можно теперь вызвать здесь
void CallPython(std::string PythonModuleName, std::string PythonFunctionName, int N, float* array, float* res_arr);



// тестовое значение:
// 100 4.39  18.81  13.42  21.17  5.39  18.82  10.64  17.17  8.66  16.59  24.26  -0.76  10.57  5.62  6.36  21.60  18.50  2.86  18.42  13.07  12.90  6.47  9.63  11.95  5.09  6.59  11.52  21.24  11.43  4.87  20.04  8.09  5.71  17.87  17.04  6.46  4.92  19.70  10.50  9.94  17.94  8.83  12.75  5.01  10.93  7.78  11.48  24.61  15.54  5.63  18.95  9.38  11.83  0.09  6.86  19.23  14.03  19.90  24.96  22.65  24.53  14.76  3.68  14.92  7.77  21.20  -0.74  20.40  4.17  14.87  15.70  4.61  9.33  24.22  11.24  19.01  0.43  17.64  24.80  2.06  21.31  3.99  8.35  0.58  18.08  7.28  14.83  5.84  7.63  9.39  12.42  11.33  0.07  3.97  7.35  13.11  10.90  11.72  13.75  23.44



int main()
{
    int n, i;
    setlocale(LC_ALL, "Russian");
    float massive[100]; // ограничение количества переменных в массиве 100 с клавиатуры ввод
    float result_array1[100]; // ограничение количества переменных в массиве 100 принимает асм и меняет его
    float result_array2[100]; // ограничение количества переменных в массиве 100 для питона
    std::cout << "Введите число n: ";
    std::cin >> n;
    std::cout << "Введите переменные для массива, x: ";
    for (i = 0; i < n; i++) {
        std::cin >> (massive[i]);
        result_array1[i] = massive[i];
    }

    func1(result_array1, n); // вызов функции asm с измененными значениями

    std::cout << std::endl << "Полученные с помощью C, masm значения:\n";
    for (i = 0; i < n; i++) { // Цикл с выводом полученных значений из masm
        std::cout << "\t result_array1[" << i << "] = ";
        printf_s("%.3f", result_array1[i]);
        std::cout << "\n";
    }

    std::cout << "\n\n\nПолученные через змею (snake)(python) значения:\n";

    CallPython("py_code", "greet", n, massive, result_array2); // 66 строка функция 
                                                               // py_code - название файла с кодом на python
                                                               // greet - функция в python, которую вызываем
    for (i = 0; i < n; i++) {
        std::cout << "\t result_array2[" << i << "] = ";
        printf_s("%.3f", result_array2[i]);
        std::cout << "\n";
    }
    std::cout << "\n\n";
    system("pause");
}


void CallPython(std::string PythonModuleName, std::string PythonFunctionName, int N, float* array, float* res_arr)
// std::string PythonModuleName - имя файла питона
// std::string PythonFunctionName - название функции в питоне
// int N - количество элементов массива
// float* array - указатель на массив, входных данных от пользователя
// float* res_arr - указатель на массив, выходные данные после питона
{

    // блок создания пемеренных, хранящих пути для поиска функции питона и файла питона
    char* funcname = new char[PythonFunctionName.length() + 1]; 
    strcpy_s(funcname, PythonFunctionName.length() + 1, PythonFunctionName.c_str());
    char* modname = new char[PythonModuleName.length() + 1];
    strcpy_s(modname, PythonModuleName.length() + 1, PythonModuleName.c_str());
    Py_Initialize(); // инициализация питона
    TCHAR cwd[2048]; // массив для хранения текущей директории, массив символов
    GetCurrentDirectory(sizeof(cwd), cwd); // запись пути текущей иректории в переенную cwd
    PyObject* sysModule = PyImport_ImportModule("sys"); // PyObject* - любой тип переменной, функция питона
    PyObject* sysPath = PyObject_GetAttrString(sysModule, "path");
    PyObject* path = PyUnicode_FromString(".");
    PyList_Append(sysPath, path); // массив питона с любым типом данных
    Py_DECREF(path);              // объявляем переменные для питона, без них не работает
    Py_DECREF(sysPath);
    Py_DECREF(sysModule);

    //блок создания переменных, указывающих на файл, функцию и результат выполнения функции
    PyObject* my_module = PyImport_ImportModule(modname); // ссылка на файл
    PyErr_Print();
    PyObject* my_function = PyObject_GetAttrString(my_module, funcname); // ссылка на функция в файле
    PyErr_Print();
    PyObject* my_result = PyObject_CallObject(my_function, NULL); // ссылка на результат в функции питона
    PyErr_Print();
    

    // блок подготовки параметров для вызова функции
    PyObject* pList = PyList_New(N); // создание массива размером N
    for (int i = 0; i < N; i++) {
        PyObject* pFloat = PyFloat_FromDouble(array[i]); // запись в pFloat i-ый элемент массива array
        PyList_SetItem(pList, i, pFloat); // кладем значение pFloat в массив pList по i-ой позиции
    }
    PyObject* pArgs = PyTuple_New(2); // pArgs - будет хранить все параметры, которую мы хотим передать в функцию питона Greet
                                     // PyTuple - упорядоченный массив любых данных
    PyTuple_SetItem(pArgs, 0, PyLong_FromLong(N)); // кладем N типа long в pArgs, нулевой элемент
    PyTuple_SetItem(pArgs, 1, pList);              // кладет массив данных pList в pArgs на первый элемент


    // блок вызова функции и получения значения 
    PyObject* pResult = PyObject_CallObject(my_function, pArgs); // pResult - результат функции в питона Greet
    Py_DECREF(pArgs); // просто надо для питона, тварь

    for (int i = 0; i < N; i++) { // Py_ssize_t - по факту длинный int 
        PyObject* item = PyList_GetItem(pResult, i);    // взять pResult по i-ой позиции и засунуть в перменную item
        double val = PyFloat_AsDouble(item);            // преобразуем даунскую форму в человеческую double
        res_arr[(int)i] = (float)val;     // кладем в res_arr по i-ой позиции результаты вычисления функции питона в типе float
    }
    Py_Finalize(); // обработка завершения работы питона

    delete[] funcname; // освобождение памяти по приколу
    delete[] modname;
}

// 15 вариант ЦУиМ 4 лаб. работа
// f(x) = ln(|cos(x) + sin(x)|)      <-- функция C
// yi = f(xi) | i = 1, n             <-- функция asm

// Доп задание:
// необходимо проанализировать, на сколько машинных циклов код в masm быстре, чем код python
// Убейте меня 
#include <iostream>
//#include <Python.h>
#include "c_func.c"
#include <locale.h>
//#include "Python.py"

extern "C" void func1(float* massive, int n); // функция в asm , которую можно теперь вызвать здесь

int main()
{

    //// Инициализация интерпретатора Python
    //Py_Initialize();

    //// Импортируем модуль mymodule
    //PyObject* pName = PyUnicode_DecodeFSDefault("Python");
    //PyObject* pModule = PyImport_Import(pName);
    //Py_DECREF(pName);

    //if (pModule != nullptr) {
    //    // Получаем функцию greet из модуля
    //    PyObject* pFunc = PyObject_GetAttrString(pModule, "greet");

    //    if (pFunc && PyCallable_Check(pFunc)) {
    //        // Создаем аргументы для функции
    //        PyObject* pArgs = PyTuple_New(1);
    //        PyObject* pValue = PyUnicode_FromString("C++ user");
    //        PyTuple_SetItem(pArgs, 0, pValue);  // передаем аргумент

    //        // Вызываем функцию
    //        PyObject* pResult = PyObject_CallObject(pFunc, pArgs);
    //        Py_DECREF(pArgs);

    //        if (pResult == nullptr) {
    //            PyErr_Print();
    //            std::cerr << "Call failed\n";
    //        }
    //        else {
    //            Py_DECREF(pResult);
    //        }
    //    }
    //    else {
    //        if (PyErr_Occurred())
    //            PyErr_Print();
    //        std::cerr << "Cannot find function 'greet'\n";
    //    }
    //    Py_XDECREF(pFunc);
    //    Py_DECREF(pModule);
    //}
    //else {
    //    PyErr_Print();
    //    std::cerr << "Failed to load 'Python'\n";
    //}

    //// Завершаем интерпретатор Python
    //Py_Finalize();
    //return 0;

    int n, i;
    setlocale(LC_ALL, "Russian");
    float massive[100]; // ограничение количества переменных в массиве 100
    std::cout << "Введите число n:";
    std::cin >> n;
    std::cout << "Введите переменные для массива, x:";
    for (i = 0; i < n; i++)
        std::cin >> (massive[i]);

    func1(massive, n); // вызов функции asm с измененными значениями

    std::cout << std::endl << "Полученные значения:\n";
    for (i = 0; i < n; i++) {
        std::cout << "\t massive[" << i << "] = ";
        printf_s("%.3f", massive[i]);
        std::cout << "\n";
    }
    system("pause");
}

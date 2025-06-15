import re           #импорт библиотек
import string
import encodings
import math

def f1(x: float) -> float:  # жестко типизируем f1 на тип float и x туда же
    return math.log(abs(math.cos(x) + math.sin(x))) # формула по варианту, которая используется в C++

def greet(N, array): # вызывается в CPP, принимает (размер массива, сам массив)
    outp = [f1(x) for x in array] # Создается переменная outp, которая является массивом, значения которого равны
                                  # значениям функции f1 от элементов массивва array
    return outp # возвращаем новый массив outp

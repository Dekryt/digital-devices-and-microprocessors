#include <stdio.h>
#include <math.h>

float c_function(float inp) { // функция принимает и возвращает тип float
    float res = 0;
    res = cos(inp) + sin(inp);
    res = fabs((float)res);
    res = log(res);

    return res;
}

#include <stdio.h>
#include <math.h>

float c_function(float inp) {
    float res = 0;
    res = cos(inp) + sin(inp);
    res = fabs((float)res);
    res = log(res);

    return res;
}

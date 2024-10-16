#include "TrigonometryClass.h"
#include "constants.h"
#include "factorial.h"
#include<iostream>
#include<math.h>


double TrigonometryClass::FuncA(double x, int n) {
    double sum_result = 0.0;

    for (int i = 0; i < n; ++i) {
        double term = (pow(-1, i) * euler_numbers[i] * pow(x, 2 * i)) / factorial(2 * i);
        sum_result += term;
    }

    return sum_result;
}

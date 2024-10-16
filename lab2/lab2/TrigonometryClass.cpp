#include "TrigonometryClass.h"
#include<vector>

unsigned long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double TrigonometryClass::FuncA(double x) {

    double sum_result = 0.0;
    std::vector<int> euler_numbers = { 1, -1, 5 };

    for (int i = 0; i < 3; ++i) {
        double term = (pow(-1, i) * euler_numbers[i] * pow(x, 2 * i)) / factorial(2 * i);
        sum_result += term;
    }

    return sum_result;
}
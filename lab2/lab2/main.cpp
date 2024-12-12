#include "TrigonometryClass.h"
#include <iostream>

#define PI 3.14
#define EPSILON 0.00001

int main() {
    TrigonometryClass calc;
    double x;
    int num_terms;
    std::cout << "Enter value of x (|x| < pi/2): ";
    std::cin >> x;

    if (abs(x) > PI / 2 - EPSILON) {
        std::cout << "Invalid x" << std::endl;
        return 0;
    }

    std::cout << "Enter number of terms (n): ";
    std::cin >> num_terms;

    double result = calc.FuncA(x, num_terms);

    std::cout << "Approximated sec(" << x << ") using " << num_terms << " number of terms: " << result << std::endl;
	return 0;
}


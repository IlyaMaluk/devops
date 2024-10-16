#include "TrigonometryClass.h"
#include <iostream>
#include "math.h"

#define PI 3.14

int main() {

    TrigonometryClass calc;
    double x;
    int num_terms;
    std::cout << "Enter value of x (|x| < pi/2): ";
    std::cin >> x;

    if (abs(x) > PI / 2 - DBL_EPSILON) {
        std::cout << "Invalid x" << std::endl;
        return 0;
    }

    std::cout << "Enter number of terms (n): ";
    std::cin >> num_terms;

    double result = calc.FuncA(x, num_terms);

    std::cout << "Approximated sec(" << x << ") using " << num_terms << " number of terms: " << result << std::endl;
	return 0;
}


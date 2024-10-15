#include <iostream>
#include <iomanip>

int main() {
    int a, b;
    double aDividedByB;

    std::cin >> a >> b;

    aDividedByB = static_cast<double>(a) / b;

    std::cout << std::fixed << std::setprecision(15) << aDividedByB << std::endl;

    return 0;
}
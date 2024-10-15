#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;
    int aMinusB = a - b;
    
    if (aMinusB > 0) {
        std::cout << ">" << std::endl;
    } else if (aMinusB < 0) {
        std::cout << "<" << std::endl;
    } else {
        std::cout << "==" << std::endl;
    }
}
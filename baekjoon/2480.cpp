#include <iostream>

int main() {
    int a, b, c = 0;
    std::cin >> a >> b >> c;

    if (a == b && b == c) {
        std::cout << 10000 + a * 1000 << std::endl;
    } else if (a == b || b == c || a == c) {
        if (a == b) {
            std::cout << 1000 + a * 100 << std::endl;
        } else if (b == c) {
            std::cout << 1000 + b * 100 << std::endl;
        } else {
            std::cout << 1000 + c * 100 << std::endl;
        }
    } else {
        if (a > b && a > c) {
            std::cout << a * 100 << std::endl;
        } else if (b > a && b > c) {
            std::cout << b * 100 << std::endl;
        } else {
            std::cout << c * 100 << std::endl;
        }
    }
}
#include <iostream>

int main() {
    int t = 0;
    std::cin >> t;

    for (int i = 0; i < t; i++) {
        int a, b = 0;
        std::cin >> a >> b;
        std::cout << a + b << std::endl;
    }
}
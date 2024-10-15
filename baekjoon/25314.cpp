#include <iostream>

int main() {
    int bytes, longCount = 0;
    std::cin >> bytes;

    longCount = bytes / 4;

    while (longCount != 0) {
        std::cout << "long ";
        longCount--;
    }
    std:: cout << "int" << std::endl;


}
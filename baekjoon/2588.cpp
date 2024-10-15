#include <iostream>
#include <string>
#include <cmath>

int main() {
    std::string a, b;
    std::cin >> a >> b;
    int a_len = a.length(), b_len = b.length();
    int result[4] = {0};

    for (int i = b_len - 1; i >= 0; i--) {
        int line = b_len - 1 - i; // 3, 4, 5번 중 어느 라인을 계산 중인지 추적
        int carry = 0;
        for (int j = a_len - 1; j >= 0; j--) {
            int product = (b[i] - '0') * (a[j] - '0') + carry;
            carry = product / 10;
            product %= 10;
            result[line] += product * pow(10, a_len - j - 1);
        }
        result[line] += carry * pow(10, a_len); // 연산 결과에 캐리값 합산
        std::cout << result[line] << std::endl;
    }

    // 6번 계산
    int finalResult = 0;
    for (int i = 0; i < 3; i++) {
        finalResult += result[i] * pow(10, i);
    }

    if (finalResult == std::stoi(a) * std::stoi(b))
        std::cout << finalResult << std::endl;
    else
        abort();

    return 0;
}
#include <iostream>

int main() {
    int hourNow, minuteNow, minuteToCook;

    std::cin >> hourNow >> minuteNow >> minuteToCook;
    minuteNow += minuteToCook;
    if (minuteNow >= 60) {
        int carry;
        carry = minuteNow / 60;
        minuteNow -= carry * 60;
        hourNow += carry;
    }
    if (hourNow >= 24) {
        hourNow -= 24;
    }
    std::cout << hourNow << " " << minuteNow << std::endl;
}
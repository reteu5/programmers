#include <iostream>
#include <cmath>
using namespace std;

int solution(int x, int y) {
    int diff = y - x;
    if (diff == 0) {
        return 0; 
    }

    // n을 기준으로 n^2과 (n^2 - n) 사이에 거리를 만드는 방법
    int n = floor(sqrt(diff));
    int max_dist = n * n;
    int second_max_dist = n * (n + 1); 

    if (diff <= max_dist) {
        return 2 * n - 1;  // n^2 이하의 경우, 1...n...1에서 충분
    } else if (diff <= second_max_dist) {
        return 2 * n;  // n^2와 (n*(n+1)) 사이의 경우 하루 추가
    } else {
        return 2 * n + 1;  // 그 이상은 n+1까지 갔다가 내려옴
    }
}

int main() {
    int x, y;
    cin >> x >> y;
    cout << solution(x, y) << endl;
    return 0;
}


/*
#include <iostream>

using namespace std;

int calcMaxFromDate(int day) {
    if (day % 2 == 0) {
        return (day / 2) * ((day / 2) + 1);
    } else {
        return ((day / 2) * ((day / 2) + 1)) + ((day / 2) + 1);
    }
}

int solution(int x, int y) {
    int diff = y - x;
    int day = 0;
    if (diff == 0) {
        return 0;
    }

    while (true) {
        day += 1;
        if (calcMaxFromDate(day) >= diff) {
            return day;
        }
    }
}

int main() {
    int x, y;
    cin >> x >> y;
    cout << solution(x, y) << endl;
    return 0;
}
*/

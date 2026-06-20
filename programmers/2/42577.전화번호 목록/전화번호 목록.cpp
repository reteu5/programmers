#include <string>
#include <vector>
#include <algorithm>

using namespace std;
// 일일히 비교 불가 -> 사전순으로 정렬?

bool solution(vector<string> phone_book) {
    bool answer = true;

    sort(phone_book.begin(), phone_book.end());
    for (int i = 0; i + 1< phone_book.size(); i++)
    {
        if (phone_book[i + 1].compare(0, phone_book[i].size(), phone_book[i]) == 0)
        {
            return false;
        }
    }
    return answer;
}
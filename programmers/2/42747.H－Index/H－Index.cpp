#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations) {
    sort(citations.rbegin(), citations.rend());
    int answer = citations.size();
    
    // 인덱스 이동하면서 비교
    // 6, 5, 3, 1, 0
    for (int i = 0; i < citations.size(); i++)
    {
        if (citations[i] < i + 1) 
        {
            answer = i;
            break;
        }
    }
    return answer;
}
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
// reserve 관점에서 판단
// 인접 번호 찾으면 
// 연속 + 퐁당 --> 연속 방향으로 빌려주어야 MAX 가능 -- (2, 3, 5)인 경우 4는 3에 빌려주어야 함.
// --> 역으로 lost 관점에서 greedy하게 가져간다면??
int solution(int n, vector<int> lost, vector<int> reserve) { 
    int answer = 0;
    
    // 여유분이 있지만, 도도도ㅗㄱ맞음
    for (int i = 0; i < lost.size();)
    {
        bool bFound = false;
        for (int j = 0; j < reserve.size(); j++)
        {
            if (lost[i] == reserve[j])
            {
                bFound = true;
                lost.erase(lost.begin() + i);
                reserve.erase(reserve.begin() + j);
                break;
            }
        }
        
        if (bFound) continue;
        else i++;
    }
    
    // 그리디 수행 위해서 오름차순 정렬 
    sort(lost.begin(), lost.end());
    sort(reserve.begin(), reserve.end());

    answer = n - lost.size();
    
    
    // 좌우 인접칸 탐색
    while (!lost.empty()) {
        for (int j = 0; j < (int)reserve.size(); ) {
            // 이미 지나간 번호 제거
            if (reserve[j] < lost.front() - 1) {
                reserve.erase(reserve.begin() + j);
                continue;
            }

            // 왼쪽 내꺼야
            if (reserve[j] == lost.front() - 1) {
                reserve.erase(reserve.begin() + j);
                ++answer;
                break;
            }

            // 오른쪽도 내끄다
            if (reserve[j] == lost.front() + 1) {
                reserve.erase(reserve.begin() + j);
                ++answer;
                break;
            }

            // 스코프 지나감
            if (reserve[j] > lost.front() + 1) {
                break;
            }

            ++j;
        }

        lost.erase(lost.begin());
    }
    
    return answer;
}


// 비용 고려 안 하면 이런 방식도 가능할듯
// for (int lostee : lost)
// {
//     auto left = find(reserve.begin(), reserve.end(), lostee - 1);
//     if (left != reserve.end()) 
//     {
//         reserve.erase(left);
//         answer++;
//         continue;
//     }

//     auto right = find(reserve.begin(), reserve.end(), lostee + 1);
//     if (right != reserve.end()) 
//     {
//         reserve.erase(right);
//         answer++;
//     }
// }
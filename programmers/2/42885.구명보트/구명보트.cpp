#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    int left = 0;
    int right = people.size() - 1;
    
    sort(people.rbegin(), people.rend()); // 내림차순 정렬
    
    while (left <= right)
    {
        if (people[left] + people[right] <= limit)
        {
            right--;
        }   // left가 제일 무거운 애니깐, 제일 가벼운 right랑도 못타면 노답임
        
        left++;
        answer++;
    }
    
    
    return answer;
}


// int solution(vector<int> people, int limit) {
//     int answer = 0;
//     int size = people.size();
    
//     vector<bool> Escaped(size, false);
//     sort(people.rbegin(), people.rend());
    
//     for (int i = 0; i < size; i++)
//     {
//         if (Escaped[i]) continue;
        
//         int next = i + 1;
//         while (next < size && (people[i] + people[next] > limit || Escaped[next] == true))
//         {
//             next++;
//         }   // 그리디하게 무거운 동료부터 판단
        
        
//         if (next >= size)  // 혼자서만 타야하는 경우
//         {
//             Escaped[i] = true;
//             answer++;
//         } 
//         else
//         {
//             Escaped[i] = true;
//             Escaped[next] = true;
//             answer++;
//         }
//     }
    
//     return answer;
// }
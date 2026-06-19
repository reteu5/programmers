#include <string>
#include <vector>

using namespace std;
// 칸 내: 양방향 중 가까운 쪽 선택
// 칸 외: 처음부터 오른쪽으로 쭉(n - 1) vs 왼쪽/오른쪽으로 가다가 가장 긴 A^w 구간에서 반대로 꺾기

int solution(string name) {
    int answer = 0;
    int size = name.size();
    int move = size - 1;    // 칸 간 이동: 오른쪽으로 쭉 이동
    
    for (int i = 0; i < size; i++)
    {
        // 칸 내 비교 (`A -> Z`가 1회 잡아먹음)
        answer += min(name[i] - 'A', 'Z' - name[i] + 1);
        
        // 칸 간 이동 (`move`와 가다가 드리프트 꺾는걸 min으로 비교)
        int next = i + 1;
        while (next < size && name[next] == 'A')
        {
            next++;
        }
        move = min(move, i * 2 + (size - next));    // 오른쪽으로 가다가 왼쪽으로 턴
        move = min(move, (size - next) * 2 + i);    // 왼쪽으로 가다가 오른쪽으로 턴
    }
    
    return answer + move;
}

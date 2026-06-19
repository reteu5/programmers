#include <string>
#include <vector>

using namespace std;
// 칸 내: 양방향 중 가까운 쪽 선택
// 칸 외: 처음부터 오른쪽으로 쭉(n - 1) vs 왼쪽/오른쪽으로 가다가 가장 긴 A^w 구간에서 반대로 꺾기

int solution(string name) {
    int answer = 0;
    int n = name.size();

    // 기본값: 오른쪽으로 끝까지 가는 경우
    int move = n - 1;

    for (int i = 0; i < n; i++) {
        // 칸 내 이동: 위/아래 중 최소
        answer += min(name[i] - 'A', 'Z' - name[i] + 1);

        // i 다음부터 이어지는 A 구간 찾기
        int next = i + 1;
        while (next < n && name[next] == 'A') {
            next++;
        }

        // 오른쪽으로 갔다가 왼쪽으로 꺾기
        move = min(move, i * 2 + (n - next));

        // 왼쪽으로 갔다가 오른쪽으로 꺾기
        move = min(move, i + (n - next) * 2);
    }

    return answer + move;
}
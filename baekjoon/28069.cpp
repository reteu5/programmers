//
// Created by reteu on 2025-06-25(수).
//
// [28069] 김밥천국의 계단
// https://www.acmicpc.net/problem/28069
// 36' 14" c
#include <iostream>
#include <deque>
#include <vector>
using namespace std;
const int INF = 1e9;

int main()
{
  int N, K;
  cin >> N >> K;

  // 1. 한 칸 올라가거나
  // 2. 현재 칸 i에서, 1.5i (내림) 으로 이동 (0번에서 2번을 하면 제자리 가능 -> 최소 횟수도 도달 가능하면 ㅇㅋ -> 최단거리 -> BFS가 유리)
  // BFS : 현재 칸에서 1번, 2번 케이스를 각각 큐에 담아서 반복 (재귀 X)
  // NOTE (c) : BFS라는 특성샹, 현재 level을 알면, 그게 곧 진행 단계(차수)가 됨.
  deque<int> queue;
  vector<int> spent(N + 1, INF);

  // 초기화
  queue.push_back(0);
  spent[0] = 0;

  while (!queue.empty()) {
    int cur = queue.front();
    queue.pop_front();
    if (cur == N) break; // 최단거리로 도달했으니 종료! (검증은 따로!)

    // 1번. 한 칸만 오르는 경우
    if (cur + 1 <= N && spent[cur + 1] == INF) { // 2번 통해서 이미 도달할 수 있었던 칸이면 INF가 아니니깐 암 오케
      spent[cur + 1] = spent[cur] + 1;
      queue.push_back(cur + 1);
    }

    // 2번. 키라키라 프리큐어 아라모드 쿠루쿠루 차지 캔디로드
    int next = int(cur + cur / 2);
    if (next <= N && spent[next] == INF) {
      spent[next] = spent[cur] + 1;
      queue.push_back(next);
    }
  }

  if (spent[N] <= K)
    cout << "minigimbob" << endl;
  else
    cout << "water" << endl;

  return 0;
}

//
// Created by reteu on 2025-06-24(화).
//
// [1941] 소문난 칠공주 (골드 3)
// https://www.acmicpc.net/problem/1941

// 00  01  02  03  04
// 05  06  07  08  09
// 10  11  12  13  14
// 15  16  17  18  19
// 20  21  22  23  24
// 1º 11' 35" c

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

char arr[5][5];
int ans = 0;
int dx[] = {-1, +1, 0, 0};
int dy[] = {0, 0, -1, +1};

// 7칸이 다 연결되어있는지 검사
bool isConnected(const vector<int>& cand) {
  // BFS/DFS로 인근 칸에 위치한 원소 찾아서 한 칸씩 징검다리 (이유랑 기존 코드 맨 아래에 있음)
  queue<int> q; // 탐색 대기열 (FIFO의 queue를 사용했으니 BFS. stack으로 갈아끼우면 바로 DFS가 됨)
  bool visited[7] = {false};
  q.push(0);  // 초기 값 세팅
  visited[0] = true;
  int cnt = 1;  // 현재 연결 검증된 칸의 개수

  while (!q.empty()) {  // 더 이상 탐색할 칸이 없을 때까지
    int idx = q.front(); q.pop();
    int cur = cand[idx];
    int x = cur / 5, y = cur % 5;

    for (int d = 0; d < 4; ++d) {
      int nx = x + dx[d], ny = y + dy[d];
      if (nx < 0 || nx > 4 || ny < 0 || ny > 4) continue;
      int adjIdx = nx * 5 + ny; // 현재 탐색중인 인접 칸의 index
      for (int k = 0; k < 7; ++k) {
        if (!visited[k] && cand[k] == adjIdx) { // 요 칸에 아직 방문한 적 없고, 지금 탐색중인 칸의 인접 칸에 해당하면
          visited[k] = true;  // 너 우리 팀 ㅇㅇ
          q.push(k);  // 탐색 대기열에 추가
          ++cnt;
        }
      }
    }
  }
  return cnt == 7;
}

void dfs(int index, int pickedCnt, int sCnt, vector<int>& cand) {
  // pickedcnt가 7이면 검사 시작
  // 조건 : sCnt > 3, cand[]는 서로 연결
  if (pickedCnt == 7) {
    if (sCnt > 3 && isConnected(cand)) ans++;
    return;
  }

  // 예외 조건
  if (25 - index < 7 - pickedCnt) return;  // 남은 학생 수 < 필요한 학생 수
  if (pickedCnt - sCnt > 3) return;  // Y파 우세가 확실



  // cand의 앞에서부터 인근 칸 하나씩 더해보기
  // index 오름차순으로 일단 7개 골라서 테스트. -> 찾으면 ans++될거고, 아니면 말고. -> 끝까지 도달하면 index 버리고 다음 index 선택해서 테스트
  // 1) 현재 idx 칸 선택
  cand.push_back(index);
  dfs(index + 1, pickedCnt + 1, sCnt + (arr[index / 5][index % 5] == 'S'), cand);
  cand.pop_back();  // index를 포함하는 모든 케이스를 탐색했음

  // 2) 현재 idx 칸 미선택
  dfs(index + 1, pickedCnt, sCnt, cand);
}

int main() {
  // 입력 배열 초기화
  for (int y = 0; y < 5; y++) {
    for (int x = 0; x < 5; x++) {
      cin >> arr[y][x];
    }
  }

  vector<int> combi;
  dfs(0, 0, 0, combi);

  cout << ans << endl;
}


// 3 + 4와 같이 분리된 블럭은 감지하지 못 함
//// 7칸이 다 연결되어있는지 검사
//bool isConnected(const vector<int>& cand) {
//  // index 기반으로 좌표 탐색
//  // 좌표에 얹어두고, 하나라도 상하좌우 고립이면 false
//  // 끝까지 확인되면 true -> flag가 필요
//  bool confirmed[7] = {false};
//
//  // 순서대로 하나를 잡아서, 상하좌우 index를 계산하고, cand에 들어있는지 확인
//  for (int i = 0; i < 7; ++i) {
//    if (confirmed[i]) continue;  // 다른 애 체크하면서 같이 확인됐으면 pass
//    // 상하좌우에 다른 애가 있는지 체크 (사실 -5, -1, +1, +5 하는게 제일 간단하긴 한데..)
//    int x = cand[i] / 5;
//    int y = cand[i] % 5;
//    bool isConnected = false;  // 인근 좌표 체크
//    for (int j = 0; j < 4; ++j) {
//      if (isConnected) continue;
//      int cX = x + dx[j];
//      int cY = y + dy[j];
//      if (cX < 0 || cX > 4 || cY < 0 || cY > 4) continue;
//      // TODO: i번째 index부터 find하도록 최적화 하면 좋겠는데..
//      isConnected = (find(cand.begin(), cand.end(), cX * 5 + cY) != cand.end()) ? true : false;
//      if (!isConnected) return false;
//    }
//  }
//  // TODO: confirmed가 전부 true이면 true를 리턴
//}
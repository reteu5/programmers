//
// Created by reteu on 2025-06-23(월).
//
// [1236] 성 지키기 (브론즈 1)
// https://www.acmicpc.net/problem/1236
// 세로와 가로로 아무 것도 없으면 ++, 다시 연산

#include <iostream>
#include <vector>

using namespace std;
int main() {
  int N, M;
  cin >> N >> M;

  vector<string> castle(N);
  for (int i = 0; i < N; i++) cin >> castle[i];

  vector<bool> rowHasGuard(N, false);
  vector<bool> colHasGuard(M, false);

  // castle 순회하며 초기화
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (castle[i][j] == 'X') {
        rowHasGuard[i] = true;
        colHasGuard[j] = true;
      }
    }
  }

  int missingRows = 0, missingCols = 0;
  for (bool b : rowHasGuard) if (!b) ++missingRows;
  for (bool b : colHasGuard) if (!b) ++missingCols;

  cout << max(missingRows, missingCols) << '\n';
  return 0;

}
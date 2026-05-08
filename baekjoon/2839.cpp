//
// Created by reteu on 2025-06-23(월).
// [2839] 설탕배달 (실버 4)
// https://www.acmicpc.net/problem/2839
// 그리디
// 3킬로 5킬로
// 4~5' 29" c

#include <iostream>
using namespace std;

int main() {
  int N, remain, k;
  cin >> N;

  // 5킬로 최대한 가져가되, 안 떨어지면 하나 줄여서 재시도
  int cnt3 = 0;
  while (N >= 0) {
    if (N % 5 == 0) {
      cout << cnt3 + N / 5 << '\n';
      return 0;
    }
    N -= 3;
    ++cnt3;
  }
  cout << -1 << '\n';
}
//
// Created by reteu on 2025-06-23(월).
//
// [2156] 포도주 시식 (실버 1)
// https://www.acmicpc.net/problem/2156
// 잡은 건 다 먹어야 됨
// 연속 3개는 다 건드릴 수 X
// 16' 10" c

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int N;
  cin >> N;

  vector<int> vec(N + 1);
  for (int i = 1; i < N + 1; i++) {
    cin >> vec[i];
  }
  // 그리디인가 싶었지만...
  // 연속 3개 건드리면 안되는 거니깐, DP로 im2, im2, im 비교하면 될 듯?

  // 경계 조건
  if (N == 1) { cout << vec[1] << endl; return 0; }
  if (N == 2) { cout << vec[1] + vec[2] << endl; return 0; }

  // 안 먹거나, 하나 먹거나, 두 개 먹거나
  vector<int> dp(N + 1);
  dp[1] = vec[1];
  dp[2] = vec[1] + vec[2];
  for (int i = 3; i <= N; i++) {
    dp[i] = max({dp[i - 1], dp[i - 2] + vec[i], dp[i - 3] + vec[i - 1] + vec[i]});
  }
  cout << dp[N] << endl;
  return 0;
}
//
// Created by reteu on 2025-06-23(월).
//
// [33850] Chill...은 내가 가장 좋아하는 소수 (실버 1)
// https://www.acmicpc.net/problem/33850
// 배점에 따라 소수를 최대/최소로 만들어야 하는 DP
// 51' 20" c

#define FAST_IO cin.tie(0)->sync_with_stdio(0);
#include <iostream>
#include <vector>
using ll = long long;
using namespace std;

vector<bool> sieve() {
  const int LIM = 2 * 1e5;
  vector<bool> prime(LIM + 1, true);
  prime[0] = prime[1] = false;
  for (int i = 2; i * i <= LIM; i++) {
    if (prime[i]) {
      for (int j = i * i; j <= LIM; j += i) prime[j] = false;
    }
  }
  return prime;
}

int main() {
  int N, A, B;
  cin >> N >> A >> B;

  vector<int> row1(N + 1), row2(N + 1);
  for (int i = 1; i <= N; i++) cin >> row1[i];
  for (int i = 1; i <= N; i++) cin >> row2[i];

  // 점수가 같으면 바로 끝
  if (A == B) {
    cout << N * A << endl;
    return 0;
  }

  // 소수 배점 A가 더 크면 1
  int flag = (A < B) ? -1 : 1;

  // 유효한 소수 연산
  const vector<bool> prime = sieve();
  auto isPrime = [&prime](int x) { return prime[x]; };

  // 주변 칸 탐색
  vector<int> vert(N + 1), horUp(N), horDown(N);
  for (int i = 1; i <= N; i++) {
    vert[i] = isPrime(row1[i] + row2[i]);
  }
  for (int i = 1; i < N; i++) {
    horUp[i] = isPrime(row1[i] + row1[i + 1]);
    horDown[i] = isPrime(row2[i] + row2[i + 1]);
  }

  // DP 시작
  // 세로로 덮거나, 가로로 두 줄 덮거나.
  const int NEG = -1e9;
  // 2단계 전, 1단계 전, 지금 점수
  int f_im2 = 0, f_im1 = NEG, f_i = 0;   // f[0]=0, f[1] 별도
  // i = 1 따로 처리
  f_im1 = flag * vert[1];

  for (int i = 2; i <= N; ++i) {
    int cand1 = f_im1 + flag * vert[i]; // 직전 상황에 세로로 하나 더 덮기
    int cand2 = f_im2 + flag * (horUp[i - 1] + horDown[i - 1]); // 전전 상황에서 가로로 덮기
    // 같은 칸에 도달했을 때, 둘 중에 최적해를 선택하고, im2와 im1도 한 칸씩 전진
    f_i = max(cand1, cand2);
    f_im2 = f_im1;
    f_im1 = f_i;
  }
  int best = (N == 1 ? f_im1 : f_i);  // N == 1인 경우 때문에 체크

  ll primeCnt = (flag == 1) ? best : -best;
  ll ans = 1LL * N * B + primeCnt * (A - B);  // 모든 타일은 b를 기준으로, 소수 타일 여부에 따라 증/감
  cout << ans << '\n';
  return 0;
}
//
// Created by reteu on 2025-06-23(월).
//
// [1292] 쉽게 푸는 문제 (브론즈 1)
// https://www.acmicpc.net/problem/1292
// 1 2 2 3 3 3 4 4 4 4 5 5 5 5 5 6 6 6 6 6 6
// 자기보다 작은 수를 다 더한 값 + 1부터 자기 번호가 시작
// 14' 53" c

#include <iostream>
#include <string>
using namespace std;
using ll = long long;

// k번까지 utils
inline int lenBlock(int k) { return k * (k + 1) / 2; }
inline int sumBlock(int k) { return k * (k + 1) * (2 * k + 1) / 6; }

ll sumUntil(int index) {
  if (index == 0) return 0;

  // 속한 블럭 찾기
  int k = 1;
  while (lenBlock(k) < index) k++;

  // 블럭 내 몇번째인지 확인
  int pos = index - lenBlock(k - 1);

  // 합 구하기
  ll sum = sumBlock(k - 1) + pos * (k);

  return sum;
}

int main() {
  int N, M;
  cin >> N >> M;

  ll sumN = sumUntil(N - 1);
  ll sumM = sumUntil(M);

  cout << sumM - sumN << endl;
}



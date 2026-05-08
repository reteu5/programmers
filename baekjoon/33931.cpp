//
// Created by reteu on 2025-06-23(월).
//
// [33931] 체크박스 누르기 (실버 1)
// https://www.acmicpc.net/problem/33931
// 22'40" c

#include <iostream>
#include <string>
#define FAST_IO cin.tie(0)->sync_with_stdio(0);
using ll = long long;
using namespace std;

int main() {
  FAST_IO;
  ll N, M;
  cin >> N >> M;

  // 클릭하는 관점에서 바라보면, M번의 클릭을 길이 N에 배분
  ll q = M / N;  // 이만큼은 매 칸마다 클릭되고..
  ll r = M % N;  // 이만큼의 간격으로 추가 클릭이 발생

  // q가 짝수라면. r만 체크하면 되고..
  // q가 홀수라면, N만큼 켜고 r만큼 끄므로 N-r
  ll ans = (q % 2 == 0) ? r : (N - r);
  cout << ans << endl;

  return 0;
}
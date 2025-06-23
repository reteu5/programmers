//
// Created by reteu on 2025-06-23(월).
//
// [1157] 단어 공부 (브론즈 1)

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;
int main() {
  unordered_map<char, int> map;

  string input;
  cin >> input;

  for(auto& c : input) {
    // 대문자로 통일
    if('a' <= c && c <= 'z') c -= 'a' - 'A';  // 소문자라면, 소문자에서 대문자까지의 차이만큼을 빼주기
      map[c]++;
  }

  // 제일 많이 발견된 index를 찾아서 원소 개수 파악
  int mx = -1;
  for (auto p : map) {
    mx = max(mx, p.second);
  }

  char ans = '?';
  int maxCount = 0;
  for (auto p : map) {
    if (p.second == mx) {
      maxCount++;
      ans = p.first;
    }
  }

  ans = (maxCount == 1) ? ans : '?';
  cout << ans << endl;
  return 0;

}
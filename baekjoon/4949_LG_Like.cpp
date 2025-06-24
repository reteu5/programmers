//
// Created by reteu on 2025-06-24(화).
//
// [4949] 균현잡힌 세상 (실버 4)
// https://www.acmicpc.net/problem/4949
// cin으로 받았었는데, getline이 훨씬 편하네.. getline 사용법 적응해두기
// 43' 13" c

#include <iostream>
#include <vector>
using namespace std;

int main() {
  string line;

  while (getline(cin, line)) {
    // 입력 종료 조건
    if (line == ".") break;

    string stack;
    bool isOK = true;

    for (char c : line) {
      // 1. 여는 괄호는 스택에 저장
      if (c == '(' || c == '[') stack.push_back(c);
      else if (c == ')' || c == ']') {
        // 2. 닫는 괄호가 맨 처음이면 false
        if (stack.empty()) { isOK = false; break; }

        // 3. 닫는 괄호가 스택의 top이랑 매칭 안되면 false
        char top = stack.back();
        stack.pop_back();

        if ((c == ')' && top != '(') ||
            (c == ']' && top != '[')) { isOK = false; break; }
      }
    }
    if (!stack.empty()) isOK = false;
    cout << (isOK ? "yes" : "no") << '\n';
  }

  return 0;
}
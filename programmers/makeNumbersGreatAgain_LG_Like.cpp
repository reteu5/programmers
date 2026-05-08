//
// Created by reteu on 2025-06-24(화).
//
// [그리디] 큰 수 만들기
// https://school.programmers.co.kr/learn/courses/30/lessons/42883?language=cpp
// 15' --" (?) c
// 문제 조건을 잘못 이해해서 sort한 다음에 큰 거부터 순서대로 뽑으려고 했었음.

#include <string>
#include <vector>

using namespace std;

string solution(string number, int k) {
	string answer = "";
	string buffer;

	for (char c : number) {
		while (buffer.size() > 0 && k > 0 && buffer.back() < c) {
			buffer.pop_back();
			k--;
		}
		buffer.push_back(c);
	}


	return buffer;
}
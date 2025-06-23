// [골드 4] 하이터치☆메모리
// https://www.acmicpc.net/problem/34031

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#define FAST_IO cin.tie(0) -> sync_with_stdio(0);
using namespace std;
using Pair = array<int, 2>;
using ll = long long;

// `(`의 개수와 `)`의 개수가 같으면 유효한 문자열
// A의 모든 접두사에 대하여 스택을 계산하고, B에서 유효한
// 입력이 너무 커서 일일히 계산은 불가능 -> 조건을 분석해서 최적 로직을 계산해야함
// A/B 각각의 balance를 계산하면서, min이 -가 되지 않을 때까지 vector에 기록
// A와 B의 balance가 부호만 반대이고, min이 유효한 케이스를 캐치

// balance(현 스택), bal의 최솟값 담는 구조체 선언
struct StrInfo {
  int bal = 0;  // 현재 계산된 높이
  int minPref = 0;  // 현재까지 bal 중 최솟값 (-되는 거 추적용)
};

// 괄호문자열 분석 (전처리)
vector<StrInfo> preProcess(const string& input) {
  vector<StrInfo> res(input.size() + 1);
  int bal = 0, min = 0;

  for (int i = 0; i < input.size(); i++) {
    bal += (input[i] == '(' ? 1 : -1);
    min = (min < bal ? min : bal);
    res[i + 1] = {bal, min};  // 1-indexing -> i 입력하면 i에 대한 데이터 반환
  }
  return res;
}

int main() {
  string A = "", B = "";
  cin >> A;
  cin >> B;

  vector<StrInfo> processedA = preProcess(A);
  vector<StrInfo> processedB = preProcess(B);

  // B에 대하여 balance 별로 min을 hash map에 모아서 정리 -> 유효한 값만 거를 예정
  unordered_map<int, vector<int>> buckets;

  for (size_t i = 1; i < processedB.size(); i++) {
    buckets[processedB[i].bal].push_back(processedB[i].minPref);
  }
  for (auto& [_, vec] : buckets) sort(vec.begin(), vec.end()); // balance에 대한 min 값을 오름차순 정렬

  // A에 대하여 balance 스캔 후, buckets에서 유효한 개수 측정하여 ans에 append
  ll ans = 0;
  for (size_t i = 1; i < processedA.size(); i++) {
    if (processedA[i].minPref < 0) continue;
    int neededMin = -processedA[i].bal; // B.min이 이 값까지인건 ㅇㅋ

    auto it = buckets.find(neededMin);
    if (it == buckets.end()) continue; // 조건을 만족하는 B.min이 없으면 pass

    // ??
    const auto& vec = it->second;
    auto lb = lower_bound(vec.begin(), vec.end(), neededMin);
    ans += vec.end() - lb;
  }

  cout << ans << endl;
  return 0;
}

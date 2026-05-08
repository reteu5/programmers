/*
    [연세워터파크]
    Source : https://www.acmicpc.net/problem/15678

    [💡: 시작/종료 지점은 자유이고, 각 값을 합연산하기 때문에 연산의 순서와는 무관하다. --> 왼쪽부터 차례대로 밟아나가도 ㅇㅋ]
    N 개의 징검다리 (2 부터 1e5까지)
    i = 시작하는 블럭의 index
    k = 징검다리에 적힌 수 (-1e9 ~ 1e9) --> score[]로 표가
    D = 한 번에 최대 건너뛸 수 있는 칸 수 (1 부터 N-1 사이의 input 내 소정의 값)
    한 번 밟은 다리는 다시 밟을 수 X
    DP[i] = MAX(DP[i+1], DP[i+2], ..., DP[i+k]) + score[i]
      - 추가 +) -> MAX() 내부에 0도 넣어야 함.
*/

#define FAST_IO cin.tie(0)->sync_with_stdio(0);
#include <iostream>
#include <vector>
#include <deque>
using namespace std;
typedef long long ll;

int main()
{
  FAST_IO;

  int N, D;
  cin >> N >> D;
  vector<ll> score(N + 1), dp(N + 1, 0);
  for (int i = 1; i <= N; i++)
  {
    cin >> score[i];
  }

  ll output = -1e18; // initialize with the smallest value
  deque<int> dq;

  for (int i = 1; i <= N; i++)
  {
    /** 슬라이딩 윈도우 조정 - 덱에 저장된 인덱스 중, 현재 위치로부터의 거리가 D를 초과하는 인덱스 제거 */
    while (!dq.empty() && dq.front() < i - D)
    {
      dq.pop_front();
    }

    // 현재 i에서 가용한 dp중의 최대값
    ll best = 0;
    if (!dq.empty())
    {
      best = dp[dq.front()];
    }
    // 지금 밟고 있는 것까지 고려하면 더 높아지나? 를 확인
    dp[i] = max(best, 0LL) + score[i];
    output = max(output, dp[i]);

    /**
     * 현재 dp[i]보다 큰 값이 없다면 기존 값은 폐기
     * 현재 dp[i]가 최대가 아니거나, 같은 값이라면 덱 후미에 push
     * (D에 의해, 현재 최대인 값이 무효가 되면 dp[i]가 해당 시점 최대값이 되기 때문)
     */
    while (!dq.empty() && dp[dq.back()] <= dp[i])
    {
      dq.pop_back();
    }
    dq.push_back(i);
  }

  cout << output << '\n';
  return 0;
}

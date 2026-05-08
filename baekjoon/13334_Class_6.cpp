/*
    [철로]
    Source: https://www.acmicpc.net/problem/13334

    # 요약
    길이 d짜리 선로를 세울 예정. (1 <= d <= 2 * 1e8)
    사람의 수 n과 각 사람의 집/사무실 위치가 주어짐. (1 <= n <= 1e5; -1e8 < Hi, Oi < 1e8)
    최대한 많은 사람의 출근 구간이 겹치도록 선로를 세울 수 때, 노선과 겹치는 사람의 최댓값을 구하여라.
    
    # 전략
    아차피 시작지접은 누군가의 집 또는 오피스 좌표로 설정하는게 가장 무난함.

    따라서, 모든 사람의 집-오피스 선분을 x좌표 순서대로 오름차순으로 정렬한 다음에, 
    가장 작은 x좌표에서부터 길이 d만큼의 선분을 선택한다고 가정하고, 
    이 경우에 겹치는 구간의 개수를 구해서 최댓값을 갱신하는 방식으로 가면 될 듯?
    --> O(n^2)인데, 스위핑 알고리즘을 사용화면 O(nlogn)으로 줄일 수 있다고 함..? 👀


*/

#include <bits/stdc++.h>
using namespace std;
#define FAST_IO cin.tie(0)->sync_with_stdio(0)
typedef long long ll;

// 이 구간 안에 들어오면 길이 d짜리로 조건 만족 가능
struct Event
{
    ll position;
    bool isTriggering;
};

int main()
{
    FAST_IO;

    int N;
    cin >> N;

    vector<pair<ll, ll>> depot;
    depot.reserve(N);

    for (int i = 0; i < N; i++)
    {
        ll h, o;
        cin >> h >> o;

        if (h <= o)  depot.emplace_back(h, o);
        else        depot.emplace_back(o, h);
    }

    ll d;
    cin >> d;


    vector<Event> events;
    events.reserve(2 * N);

    for (int i = 0; i < N; i++)
    {
        ll point1 = depot[i].first;
        ll point2 = depot[i].second;
        // d로 커버가 안되는, 구제가 불가능한 중생인 경우 방생
        if (point2 - point1 > d)   continue;

        ll eventStart = point2 - d;
        ll eventEnd = point1;
        events.push_back(Event{eventStart, true});
        events.push_back(Event{eventEnd, false});
    }

    // events의 원소들을 position 오름차순으로 정렬
    sort(events.begin(), events.end(), [&](const Event a, const Event b) {
        if (a.position != b.position)   return a.position < b.position;
        // position이 같은 경우, triggering이 true인 것이 먼저 오도록 정렬
        return a.isTriggering > b.isTriggering; // a.isTrrigering만 리턴하게 할 경우, 두 events가 완전히 동일한 상황에서 segfault가 발생하게 됨
    });


    int currentOverlap = 0;
    int maxOverlap = 0;
    for (const auto &event : events)
    {
        if (event.isTriggering)     currentOverlap++;
        else                        currentOverlap--;

        maxOverlap = max(maxOverlap, currentOverlap);
    }

    cout << maxOverlap << endl;
}
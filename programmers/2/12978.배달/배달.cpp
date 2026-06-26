#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define INF 1e9

int solution(int N, vector<vector<int>> road, int K) {
    int answer = 0;
    vector<vector<int>> costs(N + 1, vector<int>(N + 1, INF));
    vector<int> dists(N + 1, INF);
    vector<bool> visited(N + 1, false);
    
    
    // costs 초기화
    for (vector<int> r : road)
    {
        int from = r[0];
        int to = r[1];
        int cost = r[2];
        
        costs[from][to] = min(cost, costs[from][to]);
        costs[to][from] = min(cost, costs[to][from]);
    }
    
    
    // 다익스트라 pair<누적비용, 현재노드>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 1});
    dists[1] = 0;
    
    while (!pq.empty())
    {
        auto [curCost, cur] = pq.top();
        pq.pop();
        
        if (visited[cur]) continue;
        visited[cur] = true;
        
        for (int next = 1; next < N + 1; next++)
        {
            if (costs[cur][next] == INF) continue;
            
            int nextCost = curCost + costs[cur][next];
            if (nextCost < dists[next])
            {
                dists[next] = nextCost;
                pq.push({nextCost, next});  // 새 경로에 의해 파생되는 경로도 모두 업데이트 필요
            }
        }
    }
    
    
    // 정담 필터링
    for (int i = 1; i < N + 1; i++)
    {
        if (dists[i] <= K) answer++;
    }
    
    return answer;
}


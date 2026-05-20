#include <string>
#include <vector>
#include <algorithm>

using namespace std;
// dist[s][k] + dist[k][a] + dist[k][b] -> 각각의 최적 부분해의 합

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 0;
    const int INF = 1e9 / 3;
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));

    for (int i = 1; i <= n; i++) 
    {
        dist[i][i] = 0;
    }
    
    for (const vector<int>& fare : fares) 
    {
        int u = fare[0];
        int v = fare[1];
        int cost = fare[2];

        dist[u][v] = cost;
        dist[v][u] = cost;
    }
    
    for (int mid = 1; mid <= n; mid++) 
    {
        for (int from = 1; from <= n; from++) 
        {
            for (int to = 1; to <= n; to++) 
            {
                if (dist[from][mid] == INF || dist[mid][to] == INF) 
                {
                    continue;
                }

                dist[from][to] = min(dist[from][to], dist[from][mid] + dist[mid][to]);
            }
        }
    }

    answer = INF;
    
    for (int k = 1; k <= n; k++) 
    {
        answer = min(answer, dist[s][k] + dist[k][a] + dist[k][b]);
    }

    return answer;
}
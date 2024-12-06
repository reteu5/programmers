/*
    source: https://www.acmicpc.net/problem/32388
    from  : https://www.acmicpc.net/category/1058
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll a, b;
int N;
const double INF = 1e18;

struct Mobis
{
    ll x;
    ll y;
};


int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> a >> b;
    cin >> N;

    vector<Mobis> mobis(N);
    for (int i = 0; i < N; i++) 
    {
        cin >> mobis[i].x >> mobis[i].y;
    }


    // 좌표 정보 초기화
    int totalNodes = N + 2;
    vector<pair<double, double>> coordinates(totalNodes, {0.0, 0.0});
    // coordinates[0] : starting point
    // coordinates[1] : destination point
    coordinates[1] = {(double)a, (double)b};
    for (int i = 0; i < N; i++)
    {
        coordinates[i + 2] = {(double)mobis[i].x, (double)mobis[i].y};
    }


    // 다익스트라 알고리즘 적용을 위한 distance/visited 벡터 정의
    vector<double> dist(totalNodes, INF);
    dist[0] = 0.0;

    vector<bool> visited(totalNodes, false);

    // 현재 위치에서 가장 가까운 노드를 찾아 dist 업데이트 (초기값 u: coor[0])
    for (int i = 0; i < totalNodes; i++)
    {
        double minDist = INF;
        int u = -1; // 현재 위치
        for (int j = 0; j < totalNodes; j++)
        {
            if (!visited[j] && dist[j] < minDist)
            {
                minDist = dist[j];
                u = j;
            }
        }
        if (u == -1) break; // 더 이상 방문할 노드가 없음.
        visited[u] = true;


        // u와 인접한 다음 노드(아직 방문 X)까지의 거리를 연산해서 dist 벡터 업데이트
        for (int k = 0; k < totalNodes; k++)
        {
            if (visited[k]) continue;
            double stress = 0.0;
            double dx = coordinates[u].first - coordinates[k].first;
            double dy = coordinates[u].second - coordinates[k].second;
            double distance = sqrt(dx * dx + dy * dy);

            if (u == 0) // 원점에서..
            {
                if (k == 1) // 바로 도착
                {
                    stress = distance;
                }
                else    // 가까운 모비스 존으로 이동
                {
                    stress = max(0.0, distance - 1.0);
                }
            }
            // 도착지에서 출발하려고 하면..
            else if (u == 1) continue;
            else // 모비스 존에서 출발하는 경우에는...           
            {
                if (k == 1) // 바로 도착
                {
                    stress = max(0.0, distance - 1.0);
                }
                else    // 가까운 모비스 존으로 이동
                {
                    stress = max(0.0, distance - 2.0);
                }
            }

            // dist 업데이트
            if (dist[u] + stress < dist[k])
            {
                dist[k] = dist[u] + stress;
            }
        }
    }

    // cout << fixed << setprecision(9) << dist[1] << '\n';
    // 0인 경우에는 '0'을 출력하고, 그렇지 않은 경우에는 소수점 10자리에서 반올림하여 9자리까지 출력
    if (dist[1] == 0.0)
    {
        cout << "0" << '\n';
    }
    else
    {
        cout << fixed << setprecision(9) << dist[1] << '\n';
    }
}
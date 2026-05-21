#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
// 유향 인접 리스트로 입력 처리 후, ICN을 parent로 알파벳 빠른 순으로 방문 경로를 리턴
unordered_map<string, vector<string>> graph;
vector<string> answer;

void dfs(string cur);
vector<string> solution(vector<vector<string>> tickets) {    
    // 입력값 핸들링
    for (const auto& ticket : tickets)
    {
        graph[ticket[0]].push_back(ticket[1]);
    }
    
    // dest 알파벳 역순으로 정렬
    for (auto& ticket : graph)
    {
        sort(ticket.second.rbegin(), ticket.second.rend());
    }
    
    dfs("ICN");
    
    // leaf node부터 depth가 올라가는 방향으로 push_back하였으므로 reverse()
    reverse(answer.begin(), answer.end());
    return answer;
}

void dfs(string cur)
{
    while(!graph[cur].empty())
    {
        string next = graph[cur].back();
        graph[cur].pop_back();
        dfs(next);
    }
    
    answer.push_back(cur);
}
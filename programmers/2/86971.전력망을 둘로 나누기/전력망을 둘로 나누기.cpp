#include <string>
#include <vector>
#include <algorithm>

using namespace std;
// DFS로 자식 노드 개수를 재귀적으로 부모 노드에 기록 + 양쪽 자식 노드의 sub_tree.size를 갱신(vertor<노드번호, abs(차이)>)

vector<vector<int>> graph;  // 그래프 정보를 담는 배열(인접 리스트)
vector<int> subtree;        // 서브 트리(자식 노드) 개수를 담는 배열
int answer = -1;

int dfs(int cur, int parent, int n);
int solution(int n, vector<vector<int>> wires) {
    graph.assign(n + 1, vector<int>());
    subtree.assign(n + 1, 0);
    answer = n;

    for (const vector<int>& wire : wires) {
        int u = wire[0];
        int v = wire[1];

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, 0, n);

    return answer;
}


int dfs(int cur, int parent, int n) {
    subtree[cur] = 1;

    for (int next : graph[cur]) {
        if (next == parent) {
            continue;
        }

        int childCount = dfs(next, cur, n);
        subtree[cur] += childCount;

        int otherCount = n - childCount;
        int diff = abs(otherCount - childCount);

        answer = min(answer, diff);
    }

    return subtree[cur];
}
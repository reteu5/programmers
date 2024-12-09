/*
    source: https://www.acmicpc.net/problem/2533
    이 사람 코드가 좀 더 간단하고 성능도 뛰어남 >>>>
    https://www.acmicpc.net/source/87288510
*/

#include <bits/stdc++.h>
using namespace std;

// 구조체 정의: 노드 정보 및 처리 상태
struct Node 
{
    int id;
    int parent;
    bool processed;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;
    
    // 인접 리스트 생성
    vector<vector<int>> adj(N+1, vector<int>());
    for(int i=0; i<N-1; ++i){
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    
    // DP 배열 초기화
    // dp0[u]: u가 얼리 어답터쟈 나이
    // dp1[u]: u가 얼리 어답터
    // 벡터를 사용하여 힙 영역에 동적으로 할당
    vector<int> dp0(N+1, 0);
    vector<int> dp1(N+1, 0);
    
    // 스택을 사용한 반복적 DFS
    // 각 노드는 한번은 방문 준비, 한번은 자식 처리 완료 후 DP 계산
    // Node 구조체 사용
    stack<Node> s;
    // 루트를 1로 설정, 부모는 0으로 (존재하지 않는 노드)
    s.push(Node{1, 0, false});
    
    while(!s.empty()){
        Node current = s.top();
        s.pop();
        
        if(!current.processed){
            // 처음 방문
            // 다시 스택에 넣고 processed 상태로 표시
            s.push(Node{current.id, current.parent, true});
            // 자식들을 스택에 넣음
            for(auto &v : adj[current.id]){
                if(v != current.parent){
                    s.push(Node{v, current.id, false});
                }
            }
        }
        else{
            // 자식들이 이미 처리된 상태
            // DP 계산
            dp1[current.id] = 1; // 자신이 얼리 어답터인 경우
            dp0[current.id] = 0; // 자신이 얼리 어답터가 아닌 경우
            for(auto &v : adj[current.id]){
                if(v != current.parent){
                    dp1[current.id] += min(dp0[v], dp1[v]);
                    dp0[current.id] += dp1[v];
                }
            }
        }
    }
    
    // 결과 출력: 루트 노드가 얼리 어답터인 경우와 아닌 경우 중 최소값
    cout << min(dp0[1], dp1[1]);
}

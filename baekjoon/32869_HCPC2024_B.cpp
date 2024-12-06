/*
    Source : https://www.acmicpc.net/problem/32869
    From : https://www.acmicpc.net/contest/view/1419


    # DFS
    # DP
    # Re-Rooting

    # 분석
    Re-rooting 이후 나뭇잎의 익힘 정도가 Even한 나무인지 확인하기 위해서는 아래의 검증을 거쳐야 한다.
    - 자기 자신의 색깔은 자신의 하위에 존재하는 모든 노드들에 대하여 B/W 중 더 많은 색이 되어야 한다.
        - 모든 자식 노드에 대한 B/W 개수를 미리 계산해두어야 한다.
        - 직계 부모 노드에게 이 값을 전달하여 부모가 빠르게 자신의 색깔을 결정할 수 있도록 해야 한다.
            - B == W인 경우, 둘 다 선택 가능하기 때문에 상위 노드에서 영향을 미칠 수 있으므로, 문제가 더 복잡하게 느껴질 수 있다.
                - 단순하게 생각했을 때에는, B == W인 경우에는 두 가지 케이스를 모두 시뮬레이션하도록 해야하는데, 만약 모든 노드에서 B == W인 케이스가 발생한다면 오버헤드가 심각해진다.
                    - 더 단순한 방식으로 문제를 break down할 수 있는 방법이 있는지 고민해보자.
                        - 생각해보니, 개별 노드의 색깔은 이미 결정되어 있음. 우리는 Even한 나무인지 검증만 진행하면 되는 것.
                        - 모든 노드의 B, W 개수를 구한 다음 Net Balance를 계산하면, Root Node의 색깔은 미리 결정되어있는 것과 마찬가지이다.
                            - 따라서, Root Node의 색깔을 먼저 결정하고, 이 색깔을 기준으로 Re-Rooting을 시도한 뒤, 모든 노드에 대하여 Even한 나무의 조건 (부모 노드의 색깔이 자식 노드들의 색깔에 의해 결정되는 색깔과 일치하는지)을 검증하면 된다. (Net Balance상 Root Node의 Desired Color가 White라면, Black인 노드로 Re-Rooting할 필요 자체가 없다는 소리)
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Maximum number of nodes (+5 Buffer)
const int MAX = 200005;

// Tree representation (vector<int> 타입의 원소를 가지는 MAX 고정 크기의 배열 adj_list 선언)
vector<int> adj_list[MAX];

// Colors: 0 for white, 1 for black
int C_color[MAX];

// Subtree counts when rooted at initial root
// (W_down[u] = number of white nodes in the subtree rooted at u)
int W_down[MAX];
int B_down[MAX];

// Re-rooted subtree counts
int W_down_re[MAX];
int B_down_re[MAX];

// Total counts
int W_total = 0;
int B_total = 0;

// Number of violations
int violation_count = 0;

// List of valid roots
vector<int> valid_roots;

// Number of nodes
int N;

// First DFS to compute W_down and B_down, and initial violations (1차 필터링 via Net Balance of colors)
void dfs1(int u, int parent){
    // Initialize counts based on color
    W_down[u] = (C_color[u] == 0) ? 1 : 0;
    B_down[u] = (C_color[u] == 1) ? 1 : 0;
    
    bool is_leaf = true;
    
    for(auto &v : adj_list[u]){
        if(v != parent){
            is_leaf = false;
            dfs1(v, u);
            W_down[u] += W_down[v];
            B_down[u] += B_down[v];
        }
    }
    
    // If not a leaf, check the condition
    if(!is_leaf){
        if(C_color[u] == 0){
            if(W_down[u] < B_down[u] + 1){
                violation_count++;
            }
        }
        else if(C_color[u] == 1){
            if(B_down[u] < W_down[u] + 1){
                violation_count++;
            }
        }
    }
}

// Second DFS to perform re-rooting
void dfs2(int u, int parent){
    for(auto &v : adj_list[u]){
        if(v != parent){
            // Backup the old counts
            int W_down_u_old = W_down_re[u];
            int B_down_u_old = B_down_re[u];
            int W_down_v_old = W_down_re[v];
            int B_down_v_old = B_down_re[v];
            
            // Adjust the counts when re-rooting to v
            W_down_re[u] -= W_down_re[v];
            B_down_re[u] -= B_down_re[v];
            
            W_down_re[v] = W_total;
            B_down_re[v] = B_total;
            
            // Check conditions before re-rooting
            bool u_before_valid = false;
            if(C_color[u] == 0){
                if(W_down_u_old >= B_down_u_old + 1){
                    u_before_valid = true;
                }
            }
            else if(C_color[u] ==1){
                if(B_down_u_old >= W_down_u_old + 1){
                    u_before_valid = true;
                }
            }
            
            bool v_before_valid = false;
            if(C_color[v] == 0){
                if(W_down_v_old >= B_down_v_old + 1){
                    v_before_valid = true;
                }
            }
            else if(C_color[v] ==1){
                if(B_down_v_old >= W_down_v_old + 1){
                    v_before_valid = true;
                }
            }
            
            // Check conditions after re-rooting
            bool u_after_valid = false;
            if(C_color[u] == 0){
                if(W_down_re[u] >= B_down_re[u] + 1){
                    u_after_valid = true;
                }
            }
            else if(C_color[u] ==1){
                if(B_down_re[u] >= W_down_re[u] + 1){
                    u_after_valid = true;
                }
            }
            
            bool v_after_valid = false;
            if(C_color[v] == 0){
                if(W_down_re[v] >= B_down_re[v] + 1){
                    v_after_valid = true;
                }
            }
            else if(C_color[v] ==1){
                if(B_down_re[v] >= W_down_re[v] + 1){
                    v_after_valid = true;
                }
            }
            
            // Remove old violations
            if(!u_before_valid){
                violation_count--;
            }
            if(!v_before_valid){
                violation_count--;
            }
            
            // Add new violations
            if(!u_after_valid){
                violation_count++;
            }
            if(!v_after_valid){
                violation_count++;
            }
            
            // If no violations, add v to the list
            if(violation_count == 0){
                valid_roots.push_back(v);
            }
            
            // Recurse on child v
            dfs2(v, u);
            
            // Restore the counts
            W_down_re[u] = W_down_u_old;
            B_down_re[u] = B_down_u_old;
            W_down_re[v] = W_down_v_old;
            B_down_re[v] = B_down_v_old;
            
            // Restore the violation_count
            if(!u_after_valid){
                violation_count--;
            }
            if(!v_after_valid){
                violation_count--;
            }
            if(!u_before_valid){
                violation_count++;
            }
            if(!v_before_valid){
                violation_count++;
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    // Read number of nodes
    cin >> N;
    
    // Read colors
    for(int i=1; i<=N; i++) cin >> C_color[i];
    
    // Read edges
    for(int i=0; i<N-1; i++){
        int u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    

    // Perform first DFS to compute W_down and B_down (Set initial root as 1 for convinience)
    dfs1(1, -1);
    
    // Compute total counts
    W_total = W_down[1];
    B_total = B_down[1];
    
    // Initialize re-rooted counts
    for(int i=1; i<=N; i++){
        W_down_re[i] = W_down[i];
        B_down_re[i] = B_down[i];
    }
    
    // If no violations, add the initial root
    if(violation_count == 0){
        valid_roots.push_back(1);
    }
    

    // Perform second DFS to re-root the tree
    dfs2(1, -1);
    
    // Sort the valid roots
    sort(valid_roots.begin(), valid_roots.end());
    
    // Remove duplicates if any (though there shouldn't be any)
    valid_roots.erase(unique(valid_roots.begin(), valid_roots.end()), valid_roots.end());
    
    // Output the results
    cout << valid_roots.size() << "\n";
    if(valid_roots.size() > 0){
        for(int i=0; i<valid_roots.size(); i++){
            if(i > 0) cout << " ";
            cout << valid_roots[i];
        }
        cout << "\n";
    }
    
    return 0;
}

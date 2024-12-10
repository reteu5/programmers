/*
    source: https://www.acmicpc.net/problem/17401
    [일하는 세포]

    # 요약
    N개의 노드
    적혈구는 1초마다 간선(;혈관) 탐 (간선 없다? 파괴)
    혈관 중에는 루프백 존재
    혈관, 1초마다 바뀜 (주기 T초)
    A에서 D초 후 B에 도착하는 모든 경로 순서쌍 알려줘


    # 입력
    ## 1번 줄
    순환 주기 T (1 ~ 100)
    거점 개수 N (2 ~ 20)
    목표 이동시간 D (0 ~ 10e9)

    ## 2번 줄
    T개의 혈관 지도가 순서대로 주어짐
    총 혈관 개수 Mi (0 ~ N^2)
    
    ## 3번 줄~ Mi개
    a b c 형식으로 입력이 주어짐
    a에서 b로 가는 혈관은 c개 (모든 혈관은 단방향 통로)

    i초부터 (i + 1)초까지 이동할 때에는 (i % T + 1)번 혈관 지도를 사용함


    # 출력
    출력은 N개의 줄로 구성
    i번째 줄에는 N개의 정수 xi1, xi2, ..., xiN을 공백으로 구분하여 출력
    xij는 0초일 때 거점 i에서 출발하여 정확히 D초가 될 때 거점 j에 도착하는 경로의 개수를 10e9+7으로 나눈 나머지 
*/

#include <bits/stdc++.h>
#define FAST_IO cin.tie(0)->sync_with_stdio(0);
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;
using Connection = pair<int, ll>;               // 도착노드와 두지점을 이어주는 통로의 수(v, c)
using Connections = vector<Connection>;         // 특정 출발노드로부터의 모든 도착노드와 그 경로의 개수
using NodeConnections = vector<Connections>;    // 모든 노드에 대한 연결 정보 (특정 시점의 혈관 지도)
using PeriodicGraph = vector<NodeConnections>;  // 전체 주기 동안의 혈관 지도 정보

// (u, p) 상태를 고유한 인덱스로 매핑하는 함수 (0-based)
int get_index(int u, int p, int T)
{
    return (u - 1) * T + p;
}

int main()
{
    FAST_IO;

    int T, N;
    ll D;
    cin >> T >> N >> D;
    // adj[p][u] = vector of (v, c), p는 0-based, u는 1-based
    PeriodicGraph adj(T, NodeConnections(N + 1, Connections()));

    // 전체 주기 동안의 혈관 지도 정보 입력 (입력 데이터 매핑)
    for(int p = 0; p < T; p++)
    {
        int Mi; // p 시점의 총 혈관 개수
        cin >> Mi;
        for(int m = 0; m < Mi; m++)
        {
            int a, b, c;    // a에서 b로 가는 혈관은 c개
            cin >> a >> b >> c;
            adj[p][a].emplace_back(b, (ll)c);   // p 시점의 a에서는... b로 가는 혈관이 c개
        }
    }

    /*
        N개의 노드가 존재할 때, 
        특정 시점 p에서의 전이행렬은 
        (u, p) 기반의 index를 기준으로 (index: (u -1)*T + p)
        row에서 column으로 향하는 통로의 개수를 
        행렬의 해당 cell에 기록한다. 
    */
    // 상태의 총 수
    int size = N * T;
    // 전이 행렬을 희소 행렬로 표현 (0-based)
    NodeConnections M(size, Connections());
    // 각 상태에서 가능한 전이를 정의 (u 발 p 시점에 )
    for(int p = 0; p < T; p++)
    {
        for(int u = 1; u <= N; u++)
        {
            for(auto &[v, c] : adj[p][u])
            {
                int next_p = (p + 1) % T;
                int from = get_index(u, p, T);
                int to = get_index(v, next_p, T);
                M[from].emplace_back(to, c);
            }
        }
    }

    // 동일한 열을 합산하여 전이 행렬을 희소 행렬로 최적화
    for(int i = 0; i < size; i++)
    {
        if(M[i].empty()) continue;
        // 도착 상태 기준으로 정렬 -> 동일한 열끼리 그룹화
        sort(M[i].begin(), M[i].end(), [&](const Connection &a, const Connection &b) 
        -> bool
        {
            return a.first < b.first;
        });
        // 동일한 열(도착 상태) 합산
        vector<pair<int, ll>> combined;
        int current = M[i][0].first;
        ll total = 0;
        for(auto &[j, val] : M[i])
        {
            if(j == current)
            {
                total = (total + val) % MOD;
            }
            else
            {
                combined.emplace_back(current, total);
                current = j;
                total = val;
            }
        }
        combined.emplace_back(current, total);
        M[i] = move(combined);
    }

    // 행렬 거듭제곱을 위한 구조체 정의
    struct MatrixStruct
    {
        int size;
        vector<Connections> mat;
        
        MatrixStruct(int s = 0) : size(s), mat(s, Connections()) {}
        
        // 행렬 곱셈 (0-based)
        MatrixStruct multiply(const MatrixStruct &other) const
        {
            MatrixStruct result(this->size);
            for(int i = 0; i < size; i++)
            {
                for(auto &[k, val_a] : this->mat[i])        // M[i][k]
                {
                    if(k >= other.size) continue;           // 안전장치
                    for(auto &[j, val_b] : other.mat[k])    // other.M[k][j]
                    {
                        // result.mat[i][j] += M[i][k] * other.M[k][j]
                        // 합산
                        bool found = false;
                        for(auto &p : result.mat[i])
                        {
                            if(p.first == j)
                            {
                                p.second = (p.second + (val_a * val_b) % MOD) % MOD;
                                found = true;
                                break;
                            }
                        }
                        if(!found)
                        {
                            result.mat[i].emplace_back(j, (val_a * val_b) % MOD);
                        }
                    }
                }
            }
            // 동일한 도착 상태를 합산
            for(int i = 0; i < size; i++)
            {
                if(result.mat[i].empty()) continue;
                // 도착 상태 기준으로 정렬 -> 동일한 열끼리 그룹화
                sort(result.mat[i].begin(), result.mat[i].end(), [&](const Connection &a, const Connection &b) 
                -> bool
                {
                    return a.first < b.first;
                });
                // 동일한 열(도착 상태) 합산
                vector<Connection> combined;
                int current = result.mat[i][0].first;
                ll total = 0;
                for(auto &[j, val] : result.mat[i])
                {
                    if(j == current)
                    {
                        total = (total + val) % MOD;
                    }
                    else
                    {
                        combined.emplace_back(current, total);
                        current = j;
                        total = val;
                    }
                }
                combined.emplace_back(current, total);
                result.mat[i] = move(combined);
            }
            return result;
        }
        
        // 행렬 거듭제곱 (0-based)
        MatrixStruct power(ll exponent) const
        {
            MatrixStruct result(this->size);
            // 단위 행렬 초기화
            for(int i = 0; i < size; i++)
            {
                result.mat[i].emplace_back(i, 1LL);
            }
            MatrixStruct base = *this;
            while(exponent > 0)
            {
                if(exponent & 1)
                {
                    result = result.multiply(base);
                }
                base = base.multiply(base);
                exponent >>= 1;
            }
            return result;
        }
    };
    
    // 전이 행렬 M을 MatrixStruct로 변환
    MatrixStruct M_matrix(size);
    for(int i =0; i < size; i++)
    {
        for(auto &[j, c] : M[i])
        {
            M_matrix.mat[i].emplace_back(j, c);
        }
    }
    
    // M^D 계산
    MatrixStruct M_power_D;
    if(D > 0)
    {
        M_power_D = M_matrix.power(D);
    }
    
    // 결과 저장을 위한 2차원 배열 초기화 (1-based)
    vector<vector<ll>> x(N + 1, vector<ll>(N + 1, 0));
    
    // 최종 주기 계산 (0-based)
    int final_p = (D % T);
    
    // 각 거점 A에 대해
    for(int A =1; A <= N; A++)
    {
        if(D == 0)
        {
            x[A][A] = 1;
            continue;
        }
        int row = get_index(A, 0, T); // 초기 상태 (A, 0)
        if(row >= M_power_D.size) continue; // 안전장치
        for(auto &[j, val] : M_power_D.mat[row]) 
        {
            // j는 최종 상태 인덱스
            int u_final = (j / T) + 1;
            int p_final = j % T;
            if(p_final == final_p)
            {
                if(u_final >=1 && u_final <=N)
                {
                    x[A][u_final] = (x[A][u_final] + val) % MOD;
                }
            }
        }
    }
    
    // D == 0인 경우는 이미 처리됨
    
    // 결과 출력 (1-based)
    for(int A =1; A <=N; A++)
    {
        for(int B =1; B <=N; B++)
        {
            cout << x[A][B];
            if(B != N) cout << ' ';
        }
        cout << '\n';
    }
}
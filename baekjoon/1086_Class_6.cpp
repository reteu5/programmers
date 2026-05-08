/*
    [박성원]
    Source: https://www.acmicpc.net/problem/1086

    # 요약
    N, 순열의 원소 N개, 나누는 수 K가 주어짐
    순열의 원소를 랜덤하게 배열해서 모든 가능한 조합을 만들 때, K로 나누어떨어질 확률 반환
    다만, 개별 원소의 최대 길이가 50자리까지 가능하기 때문에, 미리 k로 mod 연산 진행만 나머지만 담도록 효율업 필요
    ## 코멘트
    여기저기에 은근히 정수론 되게 많이 쓰이네..
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FAST_IO cin.tie(0)->sync_with_stdio(0)

// Function to compute A mod K where A is given as a string
ll compute_mod(const string& num, int K) {
    ll res = 0;
    for(char c : num){
        res = (res * 10 + (c - '0')) % K;
    }
    return res;
}

// Function to compute (10^power) mod K
ll power_mod(int power, int K){
    ll res = 1;
    for(int i=0;i<power;i++) {
        res = (res * 10) % K;
    }
    return res;
}

// Function to compute N!
ll factorial(int N){
    ll res = 1;
    for(int i=2;i<=N;i++) res *= i;
    return res;
}

// Function to compute GCD
ll gcd_func(ll a, ll b){
    while(b){
        ll tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int main()
{
    FAST_IO;
    int N, K;

    cin >> N;
    vector<string> nums(N);
    for (int i = 0; i < N; i++) cin >> nums[i];
    cin >> K;

    // 입력 배열, 10^i mod K 미리 연산
    vector<int> len(N);
    vector<ll> A_mod(N);
    vector<ll> pow10_mod(N); 



    for(int i=0;i<N;i++){
        len[i] = nums[i].size();
        A_mod[i] = compute_mod(nums[i], K);
        // Compute 10^{len[i]} mod K
        ll temp = 1;
        for(int j=0;j<len[i];j++) {
            temp = (temp * 10) % K;
        }
        pow10_mod[i] = temp;
    }
    
    // Initialize DP
    // DP[mask][mod] = number of ways
    // mask goes from 0 to (1<<N)-1
    // mod goes from 0 to K-1
    vector<vector<ll>> DP(1<<N, vector<ll>(K, 0));
    DP[0][0] = 1;
    
    for(int mask=0; mask<(1<<N); mask++){
        for(int mod=0; mod<K; mod++){
            if(DP[mask][mod] == 0) continue;
            for(int i=0; i<N; i++){
                if(!(mask & (1<<i))){
                    int new_mask = mask | (1<<i);
                    ll new_mod = ( (mod * pow10_mod[i]) % K + A_mod[i] ) % K;
                    DP[new_mask][new_mod] += DP[mask][mod];
                }
            }
        }
    }
    
    ll valid = DP[(1<<N)-1][0];
    // Compute N!
    ll total = 1;
    for(int i=2;i<=N;i++) total *= i;
    
    if(valid == 0){
        cout << "0/1";
        return 0;
    }
    if(valid == total){
        cout << "1/1";
        return 0;
    }
    ll g = gcd_func(valid, total);
    valid /= g;
    total /= g;
    cout << valid << "/" << total;
}  
/*
    [너 봄에는 캡사이신이 맛있단다]
    source: https://www.acmicpc.net/problem/15824

    # 요약
    N개의 원소로 이루어진 집합이 주어진다.
    이 집합의 모든 부분집합에 대해서 Max - min을 구하고, 그 합을 반환하라.

    # 전략
    1. 집합을 오름차순 정렬한 다음, 
    2. 부분집합에서 자신이 Max 또는 min이 되는 횟수를 고려하여
        - min : 자신보다 작은 원소를 제외한 부분집합의 개수
        - Max : 자신보다 큰 원소를 제외한 부분집합의 개수
    3. res 연산 
*/

#include <bits/stdc++.h>
#define FAST_IO cin.tie(0)->sync_with_stdio(0);

using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;


ll power(ll base, ll exp) {
    ll result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    vector<int> wooNaHotPepper(n);
    for (int i = 0; i < n; i++) {
        cin >> wooNaHotPepper[i];
    }

    // 오름차순 정렬
    sort(wooNaHotPepper.begin(), wooNaHotPepper.end());

    // 미리 2^i 값 계산
    vector<ll> powers(n);
    for (int i = 0; i < n; i++) {
        powers[i] = power(2, i);
    }

    ll result = 0;

    for (int i = 0; i < n; i++) {
        ll max_contrib = (wooNaHotPepper[i] * powers[i]) % MOD; // 최댓값 기여분
        ll min_contrib = (wooNaHotPepper[i] * powers[n - i - 1]) % MOD; // 최솟값 기여분
        result = (result + max_contrib - min_contrib + MOD) % MOD; // 모듈러 연산으로 값 갱신
    }

    cout << result << endl;
    return 0;
}
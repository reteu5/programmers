/*
    [구간 합 구하기]
    Source : https://www.acmicpc.net/problem/2042

    # 요약
    N개의 수, M번의 값 변경, 구간의 합을 구하는 횟수 K가 주어질 때, 구간의 합을 구하여라.
*/

#include <bits/stdc++.h>
#define FAST_IO cin.tie(0)->sync_with_stdio(0)
using namespace std;
typedef long long ll;


struct FenwickTree {
    int size;
    vector<ll> tree;

    FenwickTree(int n) : size(n), tree(n + 1, 0) {}

    void update(int idx, ll value) {
        while (idx <= size) {
            tree[idx] += value;
            idx += (idx & -idx);
        }
    }

    ll query(int idx) const {
        ll result = 0;
        int i = idx;
        while (i > 0) {
            result += tree[i];
            i -= (i & -i);
        }
        return result;
    }

    ll range_query(int left, int right) const {
        return query(right) - query(left - 1);
    }
};

int main()
{
    FAST_IO;

    int N, M, K;
    cin >> N >> M >> K;

    vector<ll> nums(N + 1); // 1-indexed
    for (int i = 1; i <= N; i++) cin >> nums[i];



    FenwickTree ft(N);
    for(int i = 1; i <= N; i++) {
        ft.update(i, nums[i]);
    }
    

    for (int i = 0; i < M + K; i++)
    {
        int a, b;
        ll c; // a == 1일 때에는 c가 int 범위를 벗어날 수 있음.
        cin >> a;
        if(a == 1)
        {
            int b;
            ll c;
            cin >> b >> c;
            ll diff = c - nums[b];
            nums[b] = c;
            ft.update(b, diff);
        }
        else if(a == 2)
        {
            int b, c;
            cin >> b >> c;
            ll sum = ft.range_query(b, c);
            cout << sum << endl;
        }
    }
}
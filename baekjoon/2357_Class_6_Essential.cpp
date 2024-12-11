/*
    [최솟값과 최댓값]
    source: https://www.acmicpc.net/problem/2357
    
    # 메모
    희소 배열 (Sparse Table)을 처음 사용해본 문제임.
    희소 테이블 -> X번의 작업을 반복해야하는 상황.
    2의 거듭제곱으로 나누어 결과를 미리 저장해두고, 이를 꺼내다가 결과를 계산하는 방식.

    가령, 처음엔 2개씩 비교하여 연산 결과를 저장하고, 
    그 다음엔 2개씩 비교한 값끼리 비교하면 결과적으로 4개의 값에 대해 연산을 수행한 것.
    (예시)
    2개씩 비교: 1번과 2번 비교, 3번과 4번 비교해서 최댓값 1번, 3번 저장.
    4개씩 비교: 1번과 3번 비교해서 최댓값 1번 저장. 2번과 4번 비교해서 최솟값 2번 저장.
    8개씩 비교: `1~4번 중 최댓값 1번, 최솟값 2번`이므로 `5~8번 중 최대/최소`와 비교하면 됨.
    (/예시) 
    
    # 요약
    N M 입력
    N개 정수 N줄에 입력
    2개 자연수 M줄에 입력
    오름차순 기준 인덱스 맟게 출력
*/

#include <bits/stdc++.h>
#define FAST_IO cin.tie(0)->sync_with_stdio(0);

using namespace std;

class SparseTable
{
public:
    int Size;
    vector<vector<int>> st_min;     // 범위 최솟값 저장, 희소Table
    vector<vector<int>> st_max;     // 범위 최댓값 저장, 희소Table
    vector<int> log_table;          // 로그 값 `log2(i)` 저장

    SparseTable(const vector<int> &arr)
    {
        this->Size = arr.size();
        int K = (int)floor(log2(Size)) + 1;     // Max(N) = 100,000; log2(100,000) = 16.6096 ~ 17
        st_min.assign(K, vector<int>(Size));
        st_max.assign(K, vector<int>(Size));
        log_table.assign(Size + 1, 0);

        // log_table 준비
        for (int i = 2; i <= Size; i++)
        {
            log_table[i] = log_table[i / 2] + 1;
        }

        // 초기값 설정
        // k = 0일 때, st_min, st_max는 arr로 초기화
        for (int i = 0; i < Size; i++)
        {
            st_min[0][i] = arr[i];
            st_max[0][i] = arr[i];
        }

        // k >= 1일 때, st_min, st_max는 이전 값과 비교하여 초기화
        for (int k = 1; k < K; k++)
        {
            for (int i = 0; i + (1 << k) <= Size; i++)
            {
                st_min[k][i] = min(st_min[k - 1][i], st_min[k - 1][i + (1 << (k - 1))]);
                st_max[k][i] = max(st_max[k - 1][i], st_max[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    // [L, R] 범위의 최솟값과 최댓값을 반환
    pair<int, int> query(int L, int R)
    {
        int length = R - L + 1;
        int k = log_table[length];
        int minimum = min(st_min[k][L], st_min[k][R - (1 << k) + 1]);
        int maximum = max(st_max[k][L], st_max[k][R - (1 << k) + 1]);
        return {minimum, maximum};
    }
};


int main()
{
    FAST_IO;

    int N, M;
    cin >> N >> M;

    vector<int> arr(N); // 편의상 1-based로 사용
    for (int &input : arr)
    {
        cin >> input;
    }

    SparseTable st(arr);

    string output;
    output.reserve(M * 21); // 최대 10자리 숫자 * M개; "각각의 정수들은 1이상 1,000,000,000이하의 값을 갖는다."

    while(M--){
        int a, b;
        cin >> a >> b;
        // 1-based 인덱스를 0-based로 변환
        int L = a - 1;
        int R = b - 1;
        pair<int, int> res = st.query(L, R);
        output += to_string(res.first) + " " + to_string(res.second) + "\n";
    }
    
    // 결과 출력
    cout << output;
}
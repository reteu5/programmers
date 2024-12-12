/*
    Source : https://www.acmicpc.net/problem/32868
    From : https://www.acmicpc.net/contest/view/1419

    # 분석
    앞에서부터 순서대로 읽으면서 그래프를 그리기
    1. 일방향의 유향 그래프로 작성
    2. 노드 하나를 선택할 때 해당 그래프의 최대 크기는 3
    3. 2개의 노드가 순환 참조를 하고 있는 경우에는 이릉 사전에 감지할 수 있어야 함.

    인덱싱 이후, 참조하려는 노드를 선택해서 DFS로 따라가면 해당 노드를 포함하는 set를 파악할 수 있음.
*/


#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

int answer = -1;
int inputSize = -1;
vector<int> inputArray;
vector<int> visited;        // 미방문(0), 방문중(1), 방문완료(2)
vector<set<int>> closure;   // 속한 폐쇄 집합을 담는 배열
vector<bool> inValid;      // 잡헙 원소의 개수가 혹시라도 3개를 초과하면 표시 (트리거 안돼야 정상)

void dfs(int index)
{
    if (visited[index] == 2) return;
    if (visited[index] == 1)
    {
        // 사이클 발생
        inValid[index] = true;
        return;
    }

    // 미방문 노드인 경우 (visited[index] == 0)
    visited[index] = 1;
    closure[index].insert(index);
    if (inputArray[index] != index)
    {
        dfs(inputArray[index]);
        closure[index].insert(closure[inputArray[index]].begin(), closure[inputArray[index]].end());
    }

    visited[index] = 2;
    if (closure[index].size() > 3)
    {
        inValid[index] = true;
    }
}

ll combinaiton(ll n, ll k)
{
    if (n < k) return 0;
    if (k == 0) return 1;
    ll res = 1;
    for (ll i = 1; i <= k; ++i) {
        res = res * (n - i + 1) / i;
    }
    return res;
}


int main()
{
    ios::sync_with_stdio(false);        // C++의 iostream을 C의 stdio와 동기화시키지 않는다. (stdio 사용 비활성화)
	cin.tie(0);                         // cin과 cout 매핑 끊기

    cin >> inputSize;
    inputArray.resize(inputSize);
    visited.resize(inputSize, 0);
    closure.resize(inputSize);
    inValid.resize(inputSize, false);

    for (int i = 0; i < inputSize; i++)
    {
        int a;
        cin >> a;
        --a; // 인덱스를 0부터 시작하도록 조정
        inputArray[i] = a;
    }

    
    // 미방문 노드에 대하여 DFS를 통해 폐쇄 집합을 초기 구성
    for (int i = 0; i < inputSize; i++)
    {
        if (visited[i] == 0)
        {
            dfs(i);
        }
            
    }


    map<set<int>, int> closure_sets;
    for (int i = 0; i < inputSize; ++i) {
        if (inValid[i]) continue;
        if (closure[i].size() > 3) continue;
        closure_sets[closure[i]] = 1; // 동일한 폐쇄 집합은 하나로 취급
    }

    int num_size1 = 0, num_size2 = 0, num_size3 = 0;
    for (auto& c : closure_sets) {
        int size = c.first.size();
        if (size == 1) num_size1++;
        else if (size == 2) num_size2++;
        else if (size == 3) num_size3++;
    }

    ll total = 0;
    // 옵션 1: 크기 1 폐쇄 3개 선택
    total += combinaiton(num_size1, 3);
    // 옵션 2: 크기 2 폐쇄 1개와 크기 1 폐쇄 1개 선택
    total += (ll)num_size2 * num_size1;
    // 옵션 3: 크기 3 폐쇄 1개 선택
    total += num_size3;

    cout << total % MOD << '\n';

    return 0;
}
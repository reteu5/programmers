/*
    [휴대폰 자판]
    Source : https://www.acmicpc.net/problem/5670

    # 요약
    트라이 자료구조를 사용하여, 입력된 단어들로 구성된 사전에서 평균 몇 번의 클릭으로 입력할 할 수 있는지 구하여라.
    단, 자동완성이 가능한 글자라면 해당 알파벳이 알잘딱으로 즉시 입력된다.
*/

#include <bits/stdc++.h>
#include <iomanip>
#define FAST_IO cin.tie(0)->sync_with_stdio(0)
using namespace std;
typedef long long ll;

struct TrieNode
{
    int children[26];
    int numChildren;
    bool isWord;

    TrieNode() : numChildren(0), isWord(false)
    {
        for (int i = 0; i < 26; i++)
        {
            children[i] = -1;
        }
    }
};


int main()
{
    FAST_IO;

    int N;
    
    // cin에 올바른 입력이 주어지는 동안 계속해서 루프
    while (cin >> N)
    {
        vector<TrieNode> trie;
        trie.emplace_back();    // 루트 노드 추가

        // N개의 단어를 임시로 입력받을 벡터
        vector<string> words(N);
        for (int i = 0; i < N; i++)
        {
            cin >> words[i];
        }

        // 트라이에 단어들을 추가
        for (const string& word : words)
        {
            int node = 0;
            for (char c : word)
            {
                int idx = c - 'a';
                if (trie[node].children[idx] == -1)
                {
                    trie[node].children[idx] = trie.size();
                    trie.emplace_back();
                    trie[node].numChildren++;
                }
                node = trie[node].children[idx];
            }
            trie[node].isWord = true;
        }


        // 버튼 누름 횟수 계산
        long long total_presses = 0;
        for(int i = 0; i < N; i++) {
            int node = 0; // 루트부터 시작
            int presses = 1; // 첫 글자는 항상 버튼 누름
            for(int j = 0; j < words[i].size(); j++) {
                if(j > 0){
                    // 현재 노드에서 버튼을 눌러야 하는지 확인
                    // 현재 노드가 여러 자식을 가지고 있거나 단어의 끝인 경우
                    if(trie[node].numChildren > 1 || trie[node].isWord){
                        presses += 1;
                    }
                }
                // 다음 노드로 이동
                char c = words[i][j];
                node = trie[node].children[c - 'a'];
            }
            total_presses += presses;
        }

        // 평균 계산
        double average = (double)total_presses / N;

        // 소수점 둘째 자리까지 출력
        cout << fixed << setprecision(2) << average << "\n";
    }
}
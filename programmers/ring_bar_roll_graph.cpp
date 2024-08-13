// https://school.programmers.co.kr/learn/courses/30/lessons/258711
// 도넛과 막대 그래프 Lv.02 [2024 KAKAO WINTER INTERNSHIP]
#include <string>
#include <vector>
using namespace std;

const int arraySize = 1e6 + 1;
int outbound[arraySize];
int inbound[arraySize];

/*
# 전략
1. 루트 노드는 쉽게 찾을 수 있음.
 - n(inbound) == 0 AND n(outbound) >= 2
   - 이 조건 때문에 문제 조건에서 그래프 개수 총합은 2 이상으로 보장해주는 것.
2. 이제 루트 노드에서 뻗어나가는 그래프는 식별할 수 있음.
 - 각 그래프의 특성에 맞도록 알잘딱하게 식별만 하면 됨.
3. 그래프 식별 전략
 - 도넛 (Ring) : 무난쓰
   - 총 개수에서 막대와 8자 제외한 만큼
 - 막대 (Bar) : n(inbound) > 1 AND n(outbound) == 0인 Terminal Node 존재
   - 알잘딱
 - 8자 (Roll) : n(inbound) >= 2 AND n(outbound) == 2
   - 알잘딱
4. 그래프 별로 순회하지 말고, 특이 정점을 찾아내는 방식으로 작동하도록
 - 어떻게든 그래프 순회해서 풀고 싶은데, 그래프 순회하면 인간적으로 너무 오래 걸림.
 - 그래프 총 개수 2개 이상이라고 해준 걸 봐도 사실 그래프 순회하라고 낸 게 아니라 센스 보려고 낸 문제같은데, 이런게 입사해서 도움되는지는 잘 모?루
*/

void setVertexArray(vector<vector<int>> edges) {
    for (int i = 0; i < edges.size(); i++) {
        int start = edges[i][0];
        int dest = edges[i][1];
        outbound[start]++;
        inbound[dest]++;
    }
}

int getRootNode() {
    for (int i = 1; i < arraySize; i++) {
        if (inbound[i] == 0 && outbound[i] >= 2) {
            return i;
        }
    }
    exit(-1);
}





vector<int> solution(vector<vector<int>> edges) {
    // [생성한 정점의 번호, 도넛 모양 그래프의 수, 막대 모양 그래프의 수, 8자 모양 그래프의 수]
    vector<int> answer;
    int numOfTotalGraph = 0;
    int numOfRing = 0;
    int numOfBar = 0;
    int numOfRoll = 0;

    answer[0] = getRootNode();
    numOfTotalGraph = outbound[answer[0]];

    return answer;
}
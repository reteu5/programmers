// https://school.programmers.co.kr/learn/courses/30/lessons/258711
// 도넛과 막대 그래프 Lv.02 [2024 KAKAO WINTER INTERNSHIP]

#include <string>
#include <vector>
using namespace std;

const int arraySize = 1e6 + 1;
int outbound[arraySize];
int inbound[arraySize];

class Graph {
    private:
        Node* node;
        Node* root;

    public:
        Graph() {
            this -> node = new Node(NULL, NULL);
            this -> root = new Node(NULL, NULL);
        }
        void setRootNode(Node* node) { this -> root = node; }
        Node* getRootNode() { return this -> root; };
        bool isRing();  // 자기 자신으로 돌아오는지
        bool isBar();   // 터미널 노드가 존재하는지
        bool isRoll();  // 자기 자신으로 돌아오는지 AND 나가는 간선이 2개 이상인 노드 포함 여부
};

class Node {
    private:
        int id;
        Node* nextNode = nullptr;
        Node* prevNode = nullptr;
    public:
        Node(int id, int nextId) {
            this -> id = id;
            nextNode -> id = nextId;
        }
        void setNextNode(int id, Node* nextNode) {
            this -> nextNode = nextNode;
            nextNode -> prevNode = this;
        };
        int getId() { return this -> id; };
        Node* getNextNode() { return this -> nextNode; };
        Node* getPrevNode() { return this -> prevNode; };
        int getNextNode(int id) { return nextNode -> getId(); }
        int getPrevNode(int id) { return prevNode -> getId(); }
};


void setVertexArray(vector<vector<int>> edges) {
    for (int i = 0; i < edges.size(); i++) {
        int start = edges[i][0];
        int dest = edges[i][1];
        outbound[start]++;
        inbound[dest]++;
    }
}

// n(inbound) == 0 AND n(outbound) > 2
int findRootNode() {
    for (int i = 0; i < arraySize; i++) {
        if (inbound[i] == 0 && outbound[i] > 2) {
            return i;
        }
    }
    exit(-1);
}

vector<int> findConnectedGraphs(int rootNode, vector<int> edges) {
    vector<int> graphs;
    int bookmark = NULL;
    // rootNode에서 출발하는 정점에 대하여 case 탐색 시작
    for(int i = 0; i < arraySize; i++) {
        if (edges[i][0] == rootNode) {
            bookmark = edges[i][1];
            // 그래프 유형을 판별하는 메서드 호출
        }

    }
    graphs.push_back(rootNode);
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i][0] == rootNode) {
            graphs.push_back(edges[i][1]);
        }
    }
    return graphs;
}


// int checkGraphType(int nominatedNode, vector<int> edges) {
//     int caseFlag = NULL;
//     // nominate부터 간선 따라 이동하면서 조건 충족하는지 체크
//     for (int i = 0; i < edges.size(); i++) {
//         if (edges[i][0] == nominatedNode) {
//             caseFlag = edges[i][1];
//             break;
//         }
//     }
//     //caseFlag 값에 따라 switch case문으로 리턴값 분기
// }


void setMapping(vector<vector<int>> edges, Node* parentNode, int bookmarkStart = NULL, int bookmarkEnd = NULL) {
    // edges를 탐색하며 parentNode에서 뻗어나가는 간선들을 mapping
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i][0] == parentNode -> getId()) {
            int nextId = edges[i][1];
            Node* nextNode = new Node(nextId, NULL);
            parentNode -> setNextNode(nextId, nextNode);
            setMapping(edges, nextNode, bookmarkStart, bookmarkEnd);
        }
    }
}




vector<int> solution(vector<vector<int>> edges) {
    vector<int> answer;
    Graph graph;
    Node* root;

    setVertexArray(edges);
    int rootNodeId = findRootNode();
    Node* rootNode = new Node(rootNodeId, NULL);
    graph.setRootNode(rootNode);
    Node* root = graph.getRootNode();

    setMapping(edges, root);

    return answer;
}
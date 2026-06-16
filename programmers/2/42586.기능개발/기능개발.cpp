#include <string>
#include <vector>
#include <queue>

using namespace std;

// 1. 완료까지 걸리는 소요일수를 역산 - ceil((100 - progresses) / speeds) --> 분자에 `분모 - 1`을 더해주는 방식으로 꼼?수 구현 가능
// 2. 이걸 queue에 우르르
// 3. 줄줄이 소세지 ㄱㄱ
// 4. queue.isEmpty() 일 떄까지 반복

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    queue<int> que;
    
    for (int i = 0; i < progresses.size(); i++)
    {
        que.push((100 - progresses[i] + (speeds[i] - 1)) / speeds[i]);
    }
    
    while (!que.empty())
    {
        int count = 1;
        int front = que.front();
        que.pop();
        
        while (!que.empty() && que.front() <= front) 
        {
            count++;
            que.pop();
        }
        
        answer.push_back(count);
        count = 0;
    }
    
    return answer;
}
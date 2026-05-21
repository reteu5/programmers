#include <string>
#include <vector>

using namespace std;
// DFS 완전 탐색으로 target과 일치하는 리프 노드의 개수 세기
int answer = 0;

int dfs(const vector<int>& numbers, int target, int index, int sum);
int solution(vector<int> numbers, int target) {
    
    return dfs(numbers, target, 0, 0);
}


int dfs(const vector<int>& numbers, int target, int index, int sum)
{
    if (index == numbers.size())
    {
        return ((target == sum) ? 1 : 0);
    }
    
    // plus, minus 각각에 대해서 DFS 수행 후, 더해나가기
    int plus = dfs(numbers, target, index + 1, sum + numbers[index]);
    int minus = dfs(numbers, target, index + 1, sum - numbers[index]);
    
    return plus + minus;
}
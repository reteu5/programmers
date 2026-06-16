#include <string>
#include <vector>
#include <stack>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    stack<int> basket;
    
    for (int move : moves)
    {
        int stackTop = 0;
        // 크레인 위이잉
        for(int i = 0; i < board.size(); i++)
        {
            if (!basket.empty()) stackTop = basket.top();
            if (board.at(i).at(move - 1) == 0) continue;
            
            basket.push(board.at(i).at(move - 1));
            board.at(i).at(move - 1) = 0;
            
            // 애니팡
            if (basket.top() == stackTop) {basket.pop(); basket.pop(); answer += 2;}
            
            break;
        }
    }
    
    return answer;
}
#include <string>
#include <vector>
#include <map>

/*
 * callings 순회하면서 일치하는 원소 찾으면 앞에 애랑 swap
*/
using namespace std;

vector<string> solution(vector<string> players, vector<string> callings) {
    vector<string> answer;
    
    // map으로 오름차순, 인덱스 정리
    map<string, int> mapped;
    int index = 0;
    for (string player : players)
    {
        mapped.insert({player, index});
        index++;
    }
        
    for (string called : callings)
    {
        auto found = mapped.find(called);
        
        string temp = players[found->second];
        players[found->second] = players[found->second - 1];
        players[found->second - 1] = temp;
        
        // 바뀐 값의 index 업데이트
        mapped.find(players[found->second])->second = found->second;
        mapped.find(players[found->second - 1])->second = found->second - 1;
    }
    
    answer = players;
    return answer;
}
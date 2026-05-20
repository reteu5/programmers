#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    
    unordered_map<string, int> mapped;
    mapped.reserve(participant.size());
    
    for (const string& part : participant)
    {
        mapped[part]++;
    }
    
    for (const string& it : completion)
    {
        if (auto found =  mapped.find(it); found != mapped.end())
        {
            if (--found->second == 0)
            {
                mapped.erase(found);
            }
        }
    }
    
    if (mapped.size() == 1)
    {
        answer = mapped.begin()->first;
    }
    
    return answer;
}
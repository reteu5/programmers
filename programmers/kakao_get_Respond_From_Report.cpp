// https://school.programmers.co.kr/learn/courses/30/lessons/92334

#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>


using namespace std;

vector<string> split(string input, char delimeter);
vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer(id_list.size(), 0);  // answer가 빈 벡터면, 나중에 answer[0]와 같이 접근이 불가해서 초기화해주는 것
    unordered_map<string, int> idIndex;  // id로 접근 가능한 index용 map
    
    // flagsCount[신고자이름]으로 index 접근 가능
    for (int i = 0; i < id_list.size(); i++)
    {
        idIndex[id_list[i]] = i;
    }
    
    unordered_map<string, unordered_set<string>> reportedMap;
    
    // 신고 내용에 따라 report[피신고자]의 value인 set에 <신고자> 원소 추가
    for (const string& log : report)
    {
        vector<string> content = split(log, ' ');
        string reporter = content[0];
        string reportee = content[1];
        
        reportedMap[reportee].insert(reporter);
    }
    
    // 피신고자의 map.size() > 2인 경우, map의 '신고자'에 맞춰 result에 ++로 반영
    for (const auto& [reportee, reporterSet] : reportedMap)
    {
        if (reporterSet.size() >= k) {
            for (const string& reporter : reporterSet) {
                answer[idIndex[reporter]]++;
            }
        }
    }
    
    return answer;
}

vector<string> split(string input, char delimeter)
{
    stringstream ss(input);
    string block;
    vector<string> ret;
    
    while(getline(ss, block, delimeter))
    {
        ret.push_back(block);
    }
    
    return ret;
}
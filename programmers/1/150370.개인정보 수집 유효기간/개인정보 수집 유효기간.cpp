#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

vector<string> split(const string& input, char delimeter);
int convertToDays(const string& date);

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;
    
    int todayDays = convertToDays(today);   // 오늘 날짜 처리

    // 약관별 보유 기한 매핑
    unordered_map<string, int> termMap;
    
    for (const string& term : terms) {
        vector<string> tokens = split(term, ' ');

        string type = tokens[0];
        int month = stoi(tokens[1]);

        termMap[type] = month;
    }

    // 수집한 개인정보별 만료기한 계싼
    for (int i = 0; i < privacies.size(); i++) {
        vector<string> tokens = split(privacies[i], ' ');

        string date = tokens[0];
        string type = tokens[1];
        int collectedDays = convertToDays(date);
        int expireStartDays = collectedDays + termMap[type] * 28;

        if (todayDays >= expireStartDays) {
            answer.push_back(i + 1);
        }
    }
    
    return answer;
}

vector<string> split(const string& input, char delimeter)
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

int convertToDays(const string& date) {
    vector<string> tokens = split(date, '.');

    int year = stoi(tokens[0]);
    int month = stoi(tokens[1]);
    int day = stoi(tokens[2]);

    return year * 12 * 28 + month * 28 + day;
}
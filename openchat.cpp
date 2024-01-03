#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string getAction(string record);
string getId(string record);
string getNickname(string record);

class User {
    private:
        string id = "";
        string nickname = "";
        bool isStay = false;
    
    public:
        User() {
            this->id = "";
            this->nickname = "";
            this->isStay = false;
        }

        User(string id, string nickname, bool isStay) {
            this->id = id;
            this->nickname = nickname;
            this->isStay = isStay;
        }
    
        void updateNickname(string newNickname) {
            this->nickname = newNickname;
        }

        string getId() {return this->id;}
        string getNickname() {return this->nickname;}
};

vector<string> solution(vector<string> record) {
    vector<string> answer;
    // 유저를 추적하기 위한 벡터
    unordered_map<string, User> userMap;

    // 배열 읽어들이는 while loop
    for (const string& rec : record) {
        string action = getAction(rec);
        string id = getId(rec);
        string nickname = getNickname(rec);

        // 첫 키워드 읽어서 액션 결정.
        User user;
        char actionChar = action[0];
        bool isExist = false;

        switch (actionChar) {
            // Enter : 객체 생성 및 초기화
            case 'E':
            // Change : 객체 유지 및 닉네임 변경
            case 'C':
                userMap[id] = User(id, nickname, true);
                break;
            // Leave : 객체 유지 및 플래그 설정
            case 'L':
                break;
            default:
                break;
        }
    }

    // 전체 레코드를 다시 순회하며 출력할 문자열을 만들어 answer에 추가
    // userList를 순회하며 id와 일치하는 유저의 nickname을 찾아 출력
    for (const string& rec : record) {
        string action = getAction(rec);
        string id = getId(rec);
        string nickname = userMap[id].getNickname();

        if (action == "Enter") {
            answer.push_back(nickname + "님이 들어왔습니다.");
        } else if (action == "Leave") {
            answer.push_back(nickname + "님이 나갔습니다.");
        } // Change의 경우, 출력에 포함되지 않으므로 처리 필요 없음
    }
    return answer;
}

string getAction(string record) {
    string action = "";
    int i = 0;
    while (record[i] != ' ') {
        action += record[i];
        i++;
    }
    return action;
}

string getId(string record) {
    string id = "";
    int i = 0;
    while (record[i] != ' ') {
        i++;
    }
    i++;
    while (record[i] != ' ' && i < record.size()) {
        id += record[i];
        i++;
    }
    return id;
}

string getNickname(string record) {
    string action = "";
    string nickname = "";
    int i = 0;
    while (record[i] != ' ') {
        action += record[i];
        i++;
    }
    if (action == "Leave") 
        return "";
    i++;

    while (record[i] != ' ') {
        i++;
    }
    i++;
    
    while (record[i] != ' ' && i < record.size()) {
        nickname += record[i];
        i++;
    }
    return nickname;
}


// int main() {
//     vector<string> record = {"Enter uid1234 Muzi", 
//                              "Enter uid4567 Prodo",
//                              "Leave uid1234",
//                              "Enter uid1234 Prodo",
//                              "Change uid4567 Ryan"};
//     vector<string> answer = solution(record);
//     return 0;
// }
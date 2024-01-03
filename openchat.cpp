#include <string>
#include <vector>

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
    vector<User> userList(record.size());

    // 배열 읽어들이는 while loop
    for (int i = 0; i < record.size(); i++) {
        string action = getAction(record[i]);
        string id = getId(record[i]);
        string nickname = getNickname(record[i]);

        // 첫 키워드 읽어서 액션 결정.
        User user;
        char actionChar = action[0];
        bool isExist = false;

        switch (actionChar) {
            // Enter : 객체 생성 및 초기화
            case 'E':
                isExist = false;
                // 기존에 입장 내역이 있는 경우
                for (int j = 0; j < userList.size(); j++) {
                    if (userList[j].getId() == id) {
                    userList[j].updateNickname(nickname);
                    isExist = true;
                    break;
                    }
                }

                if (!isExist) {
                    User user(id, nickname, true);
                    userList.push_back(user);
                }
                
                break;

            // Leave : 객체 유지 및 플래그 설정
            case 'L':
                break;

            // Change : 객체 유지 및 닉네임 변경
            case 'C':
                // userList를 순회하며 id가 일치하는 유저의 닉네임을 변경
                for (int j = 0; j < userList.size(); j++) {
                    if (userList[j].getId() == id) {
                        userList[j].updateNickname(nickname);
                    }   
                }
                break;

            default:
                break;
        }
    }

    // 전체 레코드를 다시 순회하며 출력할 문자열을 만들어 answer에 추가
    for (int i = 0; i < record.size(); i++) {
        string action = getAction(record[i]);
        string id = getId(record[i]);
    
        // userList를 순회하며 id와 일치하는 유저의 nickname을 찾아 출력
        for (int j = 0; j < userList.size(); j++) {
            if (userList[j].getId() == id) {
                string nickname = userList[j].getNickname();
                string actionStr = "";
                if (action == "Enter") {
                    actionStr = "들어왔습니다.";
                } else if (action == "Leave") {
                    actionStr = "나갔습니다.";
                } else if (action == "Change") {
                    break;
                }
                string answerStr = nickname + "님이 " + actionStr;
                answer.push_back(answerStr);
            }
        }

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
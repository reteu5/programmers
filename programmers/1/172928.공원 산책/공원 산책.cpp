#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

vector<string> split(const string& input, char delimiter);

vector<int> solution(vector<string> park, vector<string> routes) {
    vector<int> answer;

    int h = park.size();
    int w = park[0].size();
    
    int x = 0;
    int y = 0;
    
    // 출발지점 스캔
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (park[i][j] == 'S')
            {
                x = j;
                y = i;
            }
        }
    }
    
    // Preset 처리
    unordered_map<char, pair<int, int>> directions =
    {
        {'W', {-1, 0}},
        {'E', {1, 0}},
        {'N', {0, -1}},
        {'S', {0, 1}}
    };
    
    // 명령 실시간으로 처리하면서 이동
    for (const string& route : routes)
    {
        vector<string> input = split(route, ' ');
        char dir = input[0][0];
        int dist = stoi(input[1]);
        
        int dx = directions[dir].first;
        int dy = directions[dir].second;
        
        
        
        int nx = x;
        int ny = y;
        
        bool valid = true;

        for (int i = 0; i < dist; i++) {
            nx += dx;
            ny += dy;

            if (nx < 0 || nx >= w || ny < 0 || ny >= h || park[ny][nx] == 'X') {
                valid = false;
                break;
            }
        }

        if (valid) {
            x = nx;
            y = ny;
        }
    }
    
    return {y, x};
    // return answer;
}

    
    
    
vector<string> split(const string& input, char delimiter) {
    stringstream ss(input);
    string block;
    vector<string> ret;

    while (getline(ss, block, delimiter)) {
        ret.push_back(block);
    }

    return ret;
}
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(const string& input, char delimiter);

vector<int> solution(vector<string> park, vector<string> routes) {
    vector<int> answer;

    vector<pair<char, int>> parsedRoutes;

    for (const string& route : routes) {
        vector<string> tokens = split(route, ' ');

        char direction = tokens[0][0];
        int distance = stoi(tokens[1]);

        parsedRoutes.push_back({direction, distance});
    }

    int row = park.size();
    int col = park[0].size();

    int curY = 0;
    int curX = 0;

    for (int y = 0; y < row; y++) {
        for (int x = 0; x < col; x++) {
            if (park[y][x] == 'S') {
                curY = y;
                curX = x;
            }
        }
    }

    for (const auto& route : parsedRoutes) {
        char direction = route.first;
        int distance = route.second;

        int dy = 0;
        int dx = 0;

        if (direction == 'N') {
            dy = -1;
        } else if (direction == 'S') {
            dy = 1;
        } else if (direction == 'W') {
            dx = -1;
        } else if (direction == 'E') {
            dx = 1;
        }

        int nextY = curY;
        int nextX = curX;

        bool canMove = true;

        for (int step = 0; step < distance; step++) {
            nextY += dy;
            nextX += dx;

            if (nextY < 0 || nextY >= row || nextX < 0 || nextX >= col) {
                canMove = false;
                break;
            }

            if (park[nextY][nextX] == 'X') {
                canMove = false;
                break;
            }
        }

        if (canMove) {
            curY = nextY;
            curX = nextX;
        }
    }

    answer.push_back(curY);
    answer.push_back(curX);

    return answer;
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
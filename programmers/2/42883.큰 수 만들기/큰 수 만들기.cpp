#include <string>
#include <vector>

using namespace std;

string solution(string number, int k) {
    string answer = "";
    string buffer;
    
    for (char c : number) {
        while (buffer.size() > 0 && k > 0 && buffer.back() < c) {
            buffer.pop_back();
            k--;
        }
        buffer.push_back(c);
    }
    
    while (k > 0)
    {
        buffer.pop_back();
        k--;
    }
    
    return buffer;
}
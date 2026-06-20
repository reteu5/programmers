#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 0;
    unordered_map<string, int> drawer;
    
    for (const vector<string>& cloth : clothes)
    {
        drawer[cloth.back()] ++;
    }
    
    int comb = 1;
    for (const auto& [k, v] : drawer)
    {
        comb = comb * (v + 1);
    }
    return (comb - 1);
}
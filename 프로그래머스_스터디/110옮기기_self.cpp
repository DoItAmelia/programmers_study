#include <string>
#include <vector>

using namespace std;

vector<string> solution(vector<string> s) {
    vector<string> answer;    
    
    for (int i = 0; i < s.size(); i++) {
        for (int j = 0; j < s[i].size(); j++) {
            if (j <= s[i].size() - 3) {
                if (s[i][j] == 1 && s[i][j + 1] == 1 && s[i][j + 2] == 0) {
                    
                }
            }
        }
    }
    
    return answer;
    
}

int main()
{
    vector<string> s = { "1110","100111100","0111111010" };
    solution(s);
}
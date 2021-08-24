#include <vector>
using namespace std;

vector<int> answer;

//당첨순위 결정 함수
void getAns(int num)
{
    // num: 일치하는 개수
    switch (num) {
    case 0:
        answer.push_back(6);
        break;
    case 1:
        answer.push_back(6);
        break;
    case 2:
        answer.push_back(5);
        break;
    case 3:
        answer.push_back(4);
        break;
    case 4:
        answer.push_back(3);
        break;
    case 5:
        answer.push_back(2);
        break;
    case 6:
        answer.push_back(1);
        break;

    }
}

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    int matchnum = 0; // 일치하는 번호의 #
    int zeronum = 0; // 민수 번호 중 안보이는 번호의 #
    for (int i = 0; i < 6; i++) {
        if (lottos[i] == 0) zeronum += 1; // 0이면 matchnum+1
        for (int j = 0; j < 6; j++) {
            // 민수번호와 로또번호가 일치하면 matchnum+1
            if (lottos[i] == win_nums[j]) matchnum += 1;
        }
    }

    int maxrank = matchnum + zeronum; // 번호가 일치할 수 있는 최대 개수
    int minrank = matchnum; // 번호가 일치하는 최소 개수
    getAns(maxrank);
    getAns(minrank);
    return answer;
}
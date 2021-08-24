#include <vector>
using namespace std;

vector<int> answer;

//��÷���� ���� �Լ�
void getAns(int num)
{
    // num: ��ġ�ϴ� ����
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
    int matchnum = 0; // ��ġ�ϴ� ��ȣ�� #
    int zeronum = 0; // �μ� ��ȣ �� �Ⱥ��̴� ��ȣ�� #
    for (int i = 0; i < 6; i++) {
        if (lottos[i] == 0) zeronum += 1; // 0�̸� matchnum+1
        for (int j = 0; j < 6; j++) {
            // �μ���ȣ�� �ζǹ�ȣ�� ��ġ�ϸ� matchnum+1
            if (lottos[i] == win_nums[j]) matchnum += 1;
        }
    }

    int maxrank = matchnum + zeronum; // ��ȣ�� ��ġ�� �� �ִ� �ִ� ����
    int minrank = matchnum; // ��ȣ�� ��ġ�ϴ� �ּ� ����
    getAns(maxrank);
    getAns(minrank);
    return answer;
}
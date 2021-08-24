#include <vector>
#include <iostream>
using namespace std;

vector<int> r;

void choose_rank(int x)
{
	if (x == 6)	r.push_back(1);
	else if (x == 5)	r.push_back(2);
	else if (x == 4)	r.push_back(3);
	else if (x == 3)	r.push_back(4);
	else if (x == 2)	r.push_back(5);
	else 	r.push_back(6);
}

vector<int> solution(vector<int> lottos, vector<int> win_nums)
{
	int cnt_zero = 0;// 민수의 번호 중 0의 #
	int cnt_same = 0;// 민수의 번호와 당첨 번호 중 일치하는 #

	for (int i = 0; i < 6; i++) {
		if (lottos[i] == 0) cnt_zero += 1;
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (lottos[i] == win_nums[j]) cnt_same += 1;
		}
	}

	int min = cnt_same;
	int max = cnt_same + cnt_zero;

	choose_rank(max);
	choose_rank(min);


	return r;

}


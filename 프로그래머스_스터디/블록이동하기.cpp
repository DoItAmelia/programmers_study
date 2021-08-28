#include <string>
#include <vector>
#include <queue>

using namespace std;

struct robot {
	int x, y; // �κ��� ������
	int dir; // �κ��� ����
	int time; // ���ݱ��� �ɸ� �ð�

	robot(int y_, int x_, int dir_, int time_) {
		x = x_;
		y = y_;
		dir = dir_;
		time = time_;
	}
};

int SIZE;

// ���ʴ�� '������-�Ʒ�-����-����'���� �̵��� �� ��(x)�� ��(y)�� ��ȭ��
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

// �湮 ���� Ȯ���ϴ� �迭
// 2������ �ƴ϶� 3������ ������, �κ��� �������� �������� �����ִ� ������ 4�����̱� ����
bool visit[100][100][4]; 


// �κ��� �����̴� ���
// 1) �ܼ� �̵�(��-�Ʒ�-����-��)
// 2) ȸ��(�������� ������ �ð�/�ݽð�, �ݴ����� ������ �ð�/�ݽð�

// 1) �ܼ� �̵��� 
bool RangeCheck(robot d, int i, vector<vector<int>>& board) {
	// �������� �̵�
	int x = d.x + dx[i];
	int y = d.y + dy[i];
	// �ݴ����� �̵�
	int nx = (d.x + dx[d.dir]) + dx[i];
	int ny = (d.y + dy[d.dir]) + dy[i];

	if (x >= 0 && x < SIZE && y >= 0 && y < SIZE // �������� �̵� �� ���� ���ΰ�
		&& nx >= 0 && nx < SIZE &&  ny >= 0 && ny < SIZE // �ݴ����� �̵� �� ���� ���ΰ�
		&& board[y][x] == 0 && board[ny][nx] == 0 // ������ & �ݴ����� �̵� �� ���� ���°�
		&& !visit[y][x][d.dir]) // �湮���� ���� ���ΰ�
		return true; // ��� ������ true
	return false; // �ϳ��� �������� ���� �� false 
}


// 2) �������� ������ ȸ���� 
// **ȸ���� ���, ȸ�� �� ������ �ݴ����� �������� �ǰ�, ������ �������� �ݴ����� �ȴ�. 
bool RotateCheck(robot d, int i, vector<vector<int>>& board) {
	// �������� �̵�
	int x = d.x + dx[i];
	int y = d.y + dy[i];
	// �ݴ����� �̵� 
	int nx = (d.x + dx[d.dir]) + dx[i];
	int ny = (d.y + dy[d.dir]) + dy[i];

	if (x >= 0 && x < SIZE && y >= 0 && y < SIZE // �������� ȸ�� �� ���� ���ΰ�
		&& nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE // �ݴ����� ȸ�� �� ���� ���ΰ�
		&& board[y][x] == 0 && board[ny][nx] == 0 // ������ & �ݴ����� ȸ�� �� ���� ���°�
		&& !visit[d.y][d.x][i]) // �湮���� ���� ���ΰ�
		return true; // ��� ������ true
	return false; // �ϳ��� �������� ���� �� false 
}

// 3) �ݴ����� ������ ȸ����
// ** 
bool OpRotateCheck(robot d, int i, vector<vector<int>>& board) {
	int x = d.x + dx[i];
	int y = d.y + dy[i];
	int nx = d.x + dx[d.dir] + dx[i];
	int ny = d.y + dy[d.dir] + dy[i];

	if (x >= 0 && x < SIZE && y >= 0 && y < SIZE // �������� ȸ�� �� ���� ���ΰ�
		&& nx >= 0 && nx < SIZE &&  ny >= 0 && ny < SIZE // �ݴ����� ȸ�� �� ���� ���ΰ�
		&& board[y][x] == 0 && board[ny][nx] == 0 // ������ & �ݴ����� ȸ�� �� ���� ���°�
		&& !visit[ny][nx][3 - d.dir]) // �湮���� ���� ���ΰ�
		return true; // ��� ������ true
	return false; // �ϳ��� �������� ���� �� false
}


int solution(vector<vector<int>> board) {
	int answer = 0; // ���� ������ ���� ���� ����
	SIZE = (int)board.size(); // INT ������ board�� �� ���� ����
	
	robot d(0, 0, 0, 0); //(0,0) ������ ����
	queue<robot> q; // drone�� ť q ����
	q.push(d); // q�� d ����

	while (q.size()) {
		// q�� ���� ���� �ִ� ���Ҹ� top�� ������ �� q���� ������
		robot top = q.front();
		q.pop();

		// ���� �湮�� �� �ִٸ� LOOP�� ���ư��� ���� ���ҷ�
		if (visit[top.y][top.x][top.dir]) continue; 
		// ó�� ���� ���̸�, �湮 ������ �����
		visit[top.y][top.x][top.dir] = true; 

		// ���� �������� (N, N)�� �����ߴٸ� time�� return�ϰ� �Լ��� �����Ѵ�
		if ((top.y == SIZE - 1 && top.x == SIZE - 1) || (top.y + dy[top.dir] == SIZE - 1 && top.x + dx[top.dir] == SIZE - 1))
			return top.time;
		
		// ���� ���� �������� �������� ���ߴٸ�
		// 1) �ܼ� �̵�(��-�Ʒ�-����-��)
		for (int i = 0; i < 4; i++) {
			if (RangeCheck(top, i, board)) {
				robot temp(top.y + dy[i], top.x + dx[i], top.dir, top.time + 1);
				q.push(temp);
			}
		}

		if (top.dir % 2 == 0) {// 0 or 2 ���� ������ �¿�
			for (int i = 1; i < 4; i += 2) {
				if (RotateCheck(top, i, board)) {//������ ȸ��
					robot temp(top.y, top.x, i, top.time + 1);
					q.push(temp);
				}
				if (OpRotateCheck(top, i, board)) {//�ݴ��� ȸ��
					robot temp(top.y + dy[top.dir] + dy[i], top.x + dx[top.dir] + dx[i], 4 - i, top.time + 1);
					q.push(temp);
				}
			}
		}
		else {// 1 or 3 ����
			for (int i = 0; i < 4; i += 2) {
				if (RotateCheck(top, i, board)) {//������ ȸ��
					robot temp(top.y, top.x, i, top.time + 1);
					q.push(temp);
				}
				if (OpRotateCheck(top, i, board)) {//�ݴ��� ȸ��
					robot temp(top.y + dy[top.dir] + dy[i], top.x + dx[top.dir] + dx[i], 2 - i, top.time + 1);
					q.push(temp);
				}
			}
		}
	}
	return answer;
}
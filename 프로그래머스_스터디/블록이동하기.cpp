#include <string>
#include <vector>
#include <queue>

using namespace std;

typedef struct DRONE {
	int x, y, dir, time;
	DRONE(int y_, int x_, int dir_, int time_) {
		x = x_;
		y = y_;
		dir = dir_;
		time = time_;
	}
}drone;

int SIZE;
int dx[4] = { 1,0,-1,0 };// 0~3 : 오른쪽부터 시계방향
int dy[4] = { 0,1,0,-1 };

int rx[4] = { -1,1,1,-1 };
int ry[4] = { 1,-1,1,-1 };

bool visit[100][100][4];

bool RangeCheck(drone d, int i, vector<vector<int>>& board) {
	int x = d.x + dx[i];
	int y = d.y + dy[i];
	int nx = d.x + dx[d.dir] + dx[i];
	int ny = d.y + dy[d.dir] + dy[i];

	if (x >= 0 && x < SIZE && nx >= 0 && nx < SIZE && y >= 0 && y < SIZE && ny >= 0 && ny < SIZE
		&& board[y][x] == 0 && board[ny][nx] == 0 && !visit[y][x][d.dir]) return true;
	return false;
}

bool RotateCheck(drone d, int i, vector<vector<int>>& board) {
	int x = d.x + dx[i];
	int y = d.y + dy[i];
	int nx = d.x + dx[d.dir] + dx[i];
	int ny = d.y + dy[d.dir] + dy[i];

	if (x >= 0 && x < SIZE && nx >= 0 && nx < SIZE && y >= 0 && y < SIZE && ny >= 0 && ny < SIZE
		&& board[y][x] == 0 && board[ny][nx] == 0 && !visit[d.y][d.x][i]) return true;
	return false;
}

bool OpRotateCheck(drone d, int i, vector<vector<int>>& board) {
	int x = d.x + dx[i];
	int y = d.y + dy[i];
	int nx = d.x + dx[d.dir] + dx[i];
	int ny = d.y + dy[d.dir] + dy[i];

	if (x >= 0 && x < SIZE && nx >= 0 && nx < SIZE && y >= 0 && y < SIZE && ny >= 0 && ny < SIZE
		&& board[y][x] == 0 && board[ny][nx] == 0 && !visit[ny][nx][3 - d.dir]) return true;
	return false;
}


int solution(vector<vector<int>> board) {
	int answer = 0;
	SIZE = (int)board.size();
	drone d(0, 0, 0, 0);//(0,0) 오른쪽 방향
	queue<drone> q;
	q.push(d);

	while (q.size()) {
		drone top = q.front();
		q.pop();
		if (visit[top.y][top.x][top.dir]) continue;
		visit[top.y][top.x][top.dir] = true;
		if ((top.y == SIZE - 1 && top.x == SIZE - 1) || (top.y + dy[top.dir] == SIZE - 1 && top.x + dx[top.dir] == SIZE - 1))
			return top.time;

		for (int i = 0; i < 4; i++) {//상하좌우 이동 4가지
			if (RangeCheck(top, i, board)) {
				drone temp(top.y + dy[i], top.x + dx[i], top.dir, top.time + 1);
				q.push(temp);
			}
		}

		if (top.dir % 2 == 0) {// 0 or 2 현재 방향이 좌우
			for (int i = 1; i < 4; i += 2) {
				if (RotateCheck(top, i, board)) {//기준점 회전
					drone temp(top.y, top.x, i, top.time + 1);
					q.push(temp);
				}
				if (OpRotateCheck(top, i, board)) {//반대점 회전
					drone temp(top.y + dy[top.dir] + dy[i], top.x + dx[top.dir] + dx[i], 4 - i, top.time + 1);
					q.push(temp);
				}
			}
		}
		else {// 1 or 3 상하
			for (int i = 0; i < 4; i += 2) {
				if (RotateCheck(top, i, board)) {//기준점 회전
					drone temp(top.y, top.x, i, top.time + 1);
					q.push(temp);
				}
				if (OpRotateCheck(top, i, board)) {//반대점 회전
					drone temp(top.y + dy[top.dir] + dy[i], top.x + dx[top.dir] + dx[i], 2 - i, top.time + 1);
					q.push(temp);
				}
			}
		}
	}
	return answer;
}
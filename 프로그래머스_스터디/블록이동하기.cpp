#include <string>
#include <vector>
#include <queue>

using namespace std;

struct robot {
	int x, y; // 로봇의 기준점
	int dir; // 로봇의 방향
	int time; // 지금까지 걸린 시간

	robot(int y_, int x_, int dir_, int time_) {
		x = x_;
		y = y_;
		dir = dir_;
		time = time_;
	}
};

int SIZE;

// 차례대로 '오른쪽-아래-왼쪽-위쪽'으로 이동할 때 행(x)과 열(y)의 변화량
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

// 방문 여부 확인하는 배열
// 2차원이 아니라 3차원인 이유는, 로봇이 기준점을 기준으로 놓여있는 방향이 4가지이기 때문
bool visit[100][100][4]; 


// 로봇이 움직이는 방법
// 1) 단순 이동(위-아래-오른-왼)
// 2) 회전(기준점을 축으로 시계/반시계, 반대점을 축으로 시계/반시계

// 1) 단순 이동시 
bool RangeCheck(robot d, int i, vector<vector<int>>& board) {
	// 기준점의 이동
	int x = d.x + dx[i];
	int y = d.y + dy[i];
	// 반대점의 이동
	int nx = (d.x + dx[d.dir]) + dx[i];
	int ny = (d.y + dy[d.dir]) + dy[i];

	if (x >= 0 && x < SIZE && y >= 0 && y < SIZE // 기준점이 이동 후 격자 안인가
		&& nx >= 0 && nx < SIZE &&  ny >= 0 && ny < SIZE // 반대점이 이동 후 격자 안인가
		&& board[y][x] == 0 && board[ny][nx] == 0 // 기준점 & 반대점에 이동 후 벽이 없는가
		&& !visit[y][x][d.dir]) // 방문하지 않은 곳인가
		return true; // 모두 만족시 true
	return false; // 하나라도 만족하지 않을 시 false 
}


// 2) 기준점을 축으로 회전시 
// **회전의 경우, 회전 후 기존의 반대점이 기준점이 되고, 기존의 기준점이 반대점이 된다. 
bool RotateCheck(robot d, int i, vector<vector<int>>& board) {
	// 기준점의 이동
	int x = d.x + dx[i];
	int y = d.y + dy[i];
	// 반대점의 이동 
	int nx = (d.x + dx[d.dir]) + dx[i];
	int ny = (d.y + dy[d.dir]) + dy[i];

	if (x >= 0 && x < SIZE && y >= 0 && y < SIZE // 기준점이 회전 후 격자 안인가
		&& nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE // 반대점이 회전 후 격자 안인가
		&& board[y][x] == 0 && board[ny][nx] == 0 // 기준점 & 반대점에 회전 후 벽이 없는가
		&& !visit[d.y][d.x][i]) // 방문하지 않은 곳인가
		return true; // 모두 만족시 true
	return false; // 하나라도 만족하지 않을 시 false 
}

// 3) 반대점을 축으로 회전시
// ** 
bool OpRotateCheck(robot d, int i, vector<vector<int>>& board) {
	int x = d.x + dx[i];
	int y = d.y + dy[i];
	int nx = d.x + dx[d.dir] + dx[i];
	int ny = d.y + dy[d.dir] + dy[i];

	if (x >= 0 && x < SIZE && y >= 0 && y < SIZE // 기준점이 회전 후 격자 안인가
		&& nx >= 0 && nx < SIZE &&  ny >= 0 && ny < SIZE // 반대점이 회전 후 격자 안인가
		&& board[y][x] == 0 && board[ny][nx] == 0 // 기준점 & 반대점에 회전 후 벽이 없는가
		&& !visit[ny][nx][3 - d.dir]) // 방문하지 않은 곳인가
		return true; // 모두 만족시 true
	return false; // 하나라도 만족하지 않을 시 false
}


int solution(vector<vector<int>> board) {
	int answer = 0; // 최종 답으로 쓰일 변수 선언
	SIZE = (int)board.size(); // INT 변수에 board의 행 개수 저장
	
	robot d(0, 0, 0, 0); //(0,0) 오른쪽 방향
	queue<robot> q; // drone형 큐 q 선언
	q.push(d); // q에 d 삽입

	while (q.size()) {
		// q의 가장 위에 있는 원소를 top에 저장한 뒤 q에서 없애줌
		robot top = q.front();
		q.pop();

		// 만약 방문한 적 있다면 LOOP로 돌아가서 다음 원소로
		if (visit[top.y][top.x][top.dir]) continue; 
		// 처음 가는 곳이면, 방문 흔적을 남기기
		visit[top.y][top.x][top.dir] = true; 

		// 만약 도착점인 (N, N)에 도착했다면 time을 return하고 함수를 종료한다
		if ((top.y == SIZE - 1 && top.x == SIZE - 1) || (top.y + dy[top.dir] == SIZE - 1 && top.x + dx[top.dir] == SIZE - 1))
			return top.time;
		
		// 만약 아직 도착점에 도달하지 못했다면
		// 1) 단순 이동(위-아래-오른-왼)
		for (int i = 0; i < 4; i++) {
			if (RangeCheck(top, i, board)) {
				robot temp(top.y + dy[i], top.x + dx[i], top.dir, top.time + 1);
				q.push(temp);
			}
		}

		if (top.dir % 2 == 0) {// 0 or 2 현재 방향이 좌우
			for (int i = 1; i < 4; i += 2) {
				if (RotateCheck(top, i, board)) {//기준점 회전
					robot temp(top.y, top.x, i, top.time + 1);
					q.push(temp);
				}
				if (OpRotateCheck(top, i, board)) {//반대점 회전
					robot temp(top.y + dy[top.dir] + dy[i], top.x + dx[top.dir] + dx[i], 4 - i, top.time + 1);
					q.push(temp);
				}
			}
		}
		else {// 1 or 3 상하
			for (int i = 0; i < 4; i += 2) {
				if (RotateCheck(top, i, board)) {//기준점 회전
					robot temp(top.y, top.x, i, top.time + 1);
					q.push(temp);
				}
				if (OpRotateCheck(top, i, board)) {//반대점 회전
					robot temp(top.y + dy[top.dir] + dy[i], top.x + dx[top.dir] + dx[i], 2 - i, top.time + 1);
					q.push(temp);
				}
			}
		}
	}
	return answer;
}
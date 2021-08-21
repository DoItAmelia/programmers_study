#include <string>
#include <vector>
#include <queue>
#include <climits> // (구. limit.h ) 자료형의 사이즈를 쉽게 알 수 있게 해줌

using namespace std;

// 차례대로 '오른쪽-위쪽-왼쪽-아래쪽'으로 이동하기 위해 사용
vector<int> dx = { 0, 1, 0, -1 }; //x좌표(행 값) 변화량
vector<int> dy = { 1, 0, -1, 0 }; //y좌표(열 값) 변화량

class Point
{
public:
    int x; // x좌표
    int y; // y좌표
    int d; // 해당 좌표로 접근하기 까지의 횟수

    Point(int x, int y, int d) {
        this->x = x;
        this->y = y;
        this->d = d;
    } //**매개변수와 멤버변수를 구분하기 위해 this 포인터 사용!
};

// < 연산자 정의
bool operator < (Point a, Point b) {
    return a.d > b.d;
}

// 게임이 끝난지 여부 확인
// 모두 0이면 true, 0이 아닌 곳이 한 곳이라도 있으면 false
bool is_finish(vector<vector<int>> board) {
    for(auto b : board) {
        for (auto bb : b) {
            if (bb != 0) return false; 
        }
    }
    return true;
}

// 인수로 주어진 좌표가 격자를 벗어났는지 여부 확인
// 안 벗어났으면 true, 벗어났으면 false
bool is_range(int r, int c) {
    return (0 <= r && r <= 3 && 0 <= c && c <= 3);
}

// (x1, y1)에서 (x2, y2)로 이동하는 최소 조작 횟수를 반환함
int get_Dist(vector<vector<int>> board, int x1, int y1, int x2, int y2)
{
    priority_queue<Point> q; // 우선순위큐 q 선언
    q.push(Point(x1, y1, 0)); // 현재 좌표의 Point 객체를 넣고, d는 0으로 초기화

    int dist[4][4]; // dist 배열 선언. 각 좌표로 접근할 때 최소 횟수
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dist[i][j] = INT_MAX; // 초기화
        }
    }
    dist[x1][y1] = 0; // 현재 좌표로 접근하는 횟수는 0

    while (!q.empty()) {
        Point cur = q.top();
        q.pop();

        int curDist = cur.d; 

        if (dist[cur.x][cur.y] < curDist) continue; // 해당 좌표로 이동하기까지 더 적은 횟수가 이미 저장되어있다면 pass
        if (cur.x == x2 && cur.y == y2) return curDist; // 목표 좌표로 이동한 경우 curDist값 

        for (int i = 0; i < 4; i++) { // 네가지 방향으로 모두 이동
            int cnt = 0;
            int nx = cur.x;
            int ny = cur.y;

            // 격자를 나가기 전까지 i일때의 방향대로 한칸씩 이동
            while (is_range(nx + dx[i], ny + dy[i])) {
                // 한칸씩 이동할때마다 cnt는 1씩, nx와 ny는 i일때의 x와 y의 변화량만큼 증가
                cnt++;
                nx += dx[i]; 
                ny += dy[i];

                if (board[nx][ny] != 0) break; // 다른 카드를 만나는 경우 while문 나가기
                if (dist[nx][ny] > curDist + cnt) { // 현재 조작 횟수가 더 적다면 
                    dist[nx][ny] = curDist + cnt; // 현재 조작 횟수로 해당 좌표 dist값 업데이트 
                    q.push(Point(nx, ny, curDist + cnt)); // 해당 좌표와 조작 횟수를 q에 삽입
                }
            }

            //ctrl+방향키로 한번에 이동하는 경우 1만 더해주기
            if (dist[nx][ny] > curDist + 1) {
                dist[nx][ny] = curDist + 1;
                q.push(Point(nx, ny, curDist + 1));
            }
        }
    }
}


// 백트래킹 구현
int solve(vector<vector<int>> board, int x, int y)
{
    if (is_finish(board)) return 0; // 만약 더 이상 남아있는 카드가 없다면 끝내기

    int ret = INT_MAX;

    // k: 맨 처음 뒤집는 카드 번호
    for (int k = 1; k <= 6; k++) {
        vector<Point> point; 
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == k) {
                    point.push_back(Point(i, j, 0)); 
                    // 카드의 좌표 point 벡터에 삽입
                    // 만약 k번 카드에 도면에 아직 존재한다면 두개가 차례대로 삽입될 것
                }
            }
        }
        if (point.empty()) continue; // 카드가 존재하지 않는다면 LOOP로 돌아감(다음 k)

        // k번 카드가 두 장 존재하는데, 둘 중 어느 카드를 먼저 뒤집을지 
        // 각각 필요한 조작 횟수(현재 위치에서 가는 거리 + 엔터 두번) 계산을 해서 더 적은 거리가 걸리는 경우를 택해야 함. 
        // (경우1) 앞에꺼(먼저 삽입된 카드)를 먼저 뒤집는 경우. 
        int cand1 = get_Dist(board, x, y, point[0].x, point[0].y)
            + get_Dist(board, point[0].x, point[0].y, point[1].x, point[1].y) + 2;
        // (2) 뒤에꺼(나중에 삽입된 카드)를 먼저 뒤집는 경우
        int cand2 = get_Dist(board, x, y, point[1].x, point[1].y)
            + get_Dist(board, point[1].x, point[1].y, point[0].x, point[0].y) + 2;

        //dfs
        board[point[0].x][point[0].y] = 0;
        board[point[1].x][point[1].y] = 0;

        ret = min(ret, min(cand1 + solve(board, point[1].x, point[1].y),
            cand2 + solve(board, point[0].x, point[0].y)));

        board[point[0].x][point[0].y] = k;
        board[point[1].x][point[1].y] = k;
    }
    return ret;
}

int solution(vector<vector<int>> board, int r, int c) {
    int answer = solve(board, r, c);
    return answer;
}
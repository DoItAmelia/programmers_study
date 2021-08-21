#include <string>
#include <vector>
#include <queue>
#include <climits> // (��. limit.h ) �ڷ����� ����� ���� �� �� �ְ� ����

using namespace std;

// ���ʴ�� '������-����-����-�Ʒ���'���� �̵��ϱ� ���� ���
vector<int> dx = { 0, 1, 0, -1 }; //x��ǥ(�� ��) ��ȭ��
vector<int> dy = { 1, 0, -1, 0 }; //y��ǥ(�� ��) ��ȭ��

class Point
{
public:
    int x; // x��ǥ
    int y; // y��ǥ
    int d; // �ش� ��ǥ�� �����ϱ� ������ Ƚ��

    Point(int x, int y, int d) {
        this->x = x;
        this->y = y;
        this->d = d;
    } //**�Ű������� ��������� �����ϱ� ���� this ������ ���!
};

// < ������ ����
bool operator < (Point a, Point b) {
    return a.d > b.d;
}

// ������ ������ ���� Ȯ��
// ��� 0�̸� true, 0�� �ƴ� ���� �� ���̶� ������ false
bool is_finish(vector<vector<int>> board) {
    for(auto b : board) {
        for (auto bb : b) {
            if (bb != 0) return false; 
        }
    }
    return true;
}

// �μ��� �־��� ��ǥ�� ���ڸ� ������� ���� Ȯ��
// �� ������� true, ������� false
bool is_range(int r, int c) {
    return (0 <= r && r <= 3 && 0 <= c && c <= 3);
}

// (x1, y1)���� (x2, y2)�� �̵��ϴ� �ּ� ���� Ƚ���� ��ȯ��
int get_Dist(vector<vector<int>> board, int x1, int y1, int x2, int y2)
{
    priority_queue<Point> q; // �켱����ť q ����
    q.push(Point(x1, y1, 0)); // ���� ��ǥ�� Point ��ü�� �ְ�, d�� 0���� �ʱ�ȭ

    int dist[4][4]; // dist �迭 ����. �� ��ǥ�� ������ �� �ּ� Ƚ��
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dist[i][j] = INT_MAX; // �ʱ�ȭ
        }
    }
    dist[x1][y1] = 0; // ���� ��ǥ�� �����ϴ� Ƚ���� 0

    while (!q.empty()) {
        Point cur = q.top();
        q.pop();

        int curDist = cur.d; 

        if (dist[cur.x][cur.y] < curDist) continue; // �ش� ��ǥ�� �̵��ϱ���� �� ���� Ƚ���� �̹� ����Ǿ��ִٸ� pass
        if (cur.x == x2 && cur.y == y2) return curDist; // ��ǥ ��ǥ�� �̵��� ��� curDist�� 

        for (int i = 0; i < 4; i++) { // �װ��� �������� ��� �̵�
            int cnt = 0;
            int nx = cur.x;
            int ny = cur.y;

            // ���ڸ� ������ ������ i�϶��� ������ ��ĭ�� �̵�
            while (is_range(nx + dx[i], ny + dy[i])) {
                // ��ĭ�� �̵��Ҷ����� cnt�� 1��, nx�� ny�� i�϶��� x�� y�� ��ȭ����ŭ ����
                cnt++;
                nx += dx[i]; 
                ny += dy[i];

                if (board[nx][ny] != 0) break; // �ٸ� ī�带 ������ ��� while�� ������
                if (dist[nx][ny] > curDist + cnt) { // ���� ���� Ƚ���� �� ���ٸ� 
                    dist[nx][ny] = curDist + cnt; // ���� ���� Ƚ���� �ش� ��ǥ dist�� ������Ʈ 
                    q.push(Point(nx, ny, curDist + cnt)); // �ش� ��ǥ�� ���� Ƚ���� q�� ����
                }
            }

            //ctrl+����Ű�� �ѹ��� �̵��ϴ� ��� 1�� �����ֱ�
            if (dist[nx][ny] > curDist + 1) {
                dist[nx][ny] = curDist + 1;
                q.push(Point(nx, ny, curDist + 1));
            }
        }
    }
}


// ��Ʈ��ŷ ����
int solve(vector<vector<int>> board, int x, int y)
{
    if (is_finish(board)) return 0; // ���� �� �̻� �����ִ� ī�尡 ���ٸ� ������

    int ret = INT_MAX;

    // k: �� ó�� ������ ī�� ��ȣ
    for (int k = 1; k <= 6; k++) {
        vector<Point> point; 
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == k) {
                    point.push_back(Point(i, j, 0)); 
                    // ī���� ��ǥ point ���Ϳ� ����
                    // ���� k�� ī�忡 ���鿡 ���� �����Ѵٸ� �ΰ��� ���ʴ�� ���Ե� ��
                }
            }
        }
        if (point.empty()) continue; // ī�尡 �������� �ʴ´ٸ� LOOP�� ���ư�(���� k)

        // k�� ī�尡 �� �� �����ϴµ�, �� �� ��� ī�带 ���� �������� 
        // ���� �ʿ��� ���� Ƚ��(���� ��ġ���� ���� �Ÿ� + ���� �ι�) ����� �ؼ� �� ���� �Ÿ��� �ɸ��� ��츦 ���ؾ� ��. 
        // (���1) �տ���(���� ���Ե� ī��)�� ���� ������ ���. 
        int cand1 = get_Dist(board, x, y, point[0].x, point[0].y)
            + get_Dist(board, point[0].x, point[0].y, point[1].x, point[1].y) + 2;
        // (2) �ڿ���(���߿� ���Ե� ī��)�� ���� ������ ���
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
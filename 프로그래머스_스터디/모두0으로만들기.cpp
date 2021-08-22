#include <string>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

bool visited[300000];
long long answer = 0;

//dfs
void dfs(vector<long long>& vt, vector<vector<int>>& graph, int parent) {

    visited[parent] = true;
    for (int i = 0; i < graph[parent].size(); i++) { 
    // parent번 노트와 연결되어있는 노드의 개수만큼 아래 과정 반복
        if (visited[graph[parent][i]]) {
            continue; // 이미 방문한 적이 있는 노드라면 LOOP로 돌아가서 다음 i 실행
        }
        // 연결되어있는 노드 중에 아직 방문 안한 노드가 있다면 해당 노드에서 다시 dfs 돌리기
        dfs(vt, graph, graph[parent][i]);
       
        answer += abs(vt[graph[parent][i]]); // 연결되어있는 노드의 가중치의 절댓값만큼 더하기 
        vt[parent] += vt[graph[parent][i]]; // 현재 노드의 가중치에 연결되어있던 가중치만큼 더해주기
    }
}

long long solution(vector<int> a, vector<vector<int>> edges) {
    vector<long long> vt(a.begin(), a.end()); //a를 long long형으로 vt에 복사
    vector<vector<int>> graph(a.size()); // a의 원소개수만큼 칸 만들기
    
    // 점들의 양쪽 연결 상태를 나타내도록 
    for (int i = 0; i < edges.size(); i++) {
        graph[edges[i][0]].push_back(edges[i][1]);
        graph[edges[i][1]].push_back(edges[i][0]);
    }
    
    dfs(vt, graph, 0); // 0번 노드를 루트로 잡고 dfs돌리기
   if (vt[0] != 0)
        return -1;
    return answer;
}

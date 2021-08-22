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
    // parent�� ��Ʈ�� ����Ǿ��ִ� ����� ������ŭ �Ʒ� ���� �ݺ�
        if (visited[graph[parent][i]]) {
            continue; // �̹� �湮�� ���� �ִ� ����� LOOP�� ���ư��� ���� i ����
        }
        // ����Ǿ��ִ� ��� �߿� ���� �湮 ���� ��尡 �ִٸ� �ش� ��忡�� �ٽ� dfs ������
        dfs(vt, graph, graph[parent][i]);
       
        answer += abs(vt[graph[parent][i]]); // ����Ǿ��ִ� ����� ����ġ�� ���񰪸�ŭ ���ϱ� 
        vt[parent] += vt[graph[parent][i]]; // ���� ����� ����ġ�� ����Ǿ��ִ� ����ġ��ŭ �����ֱ�
    }
}

long long solution(vector<int> a, vector<vector<int>> edges) {
    vector<long long> vt(a.begin(), a.end()); //a�� long long������ vt�� ����
    vector<vector<int>> graph(a.size()); // a�� ���Ұ�����ŭ ĭ �����
    
    // ������ ���� ���� ���¸� ��Ÿ������ 
    for (int i = 0; i < edges.size(); i++) {
        graph[edges[i][0]].push_back(edges[i][1]);
        graph[edges[i][1]].push_back(edges[i][0]);
    }
    
    dfs(vt, graph, 0); // 0�� ��带 ��Ʈ�� ��� dfs������
   if (vt[0] != 0)
        return -1;
    return answer;
}

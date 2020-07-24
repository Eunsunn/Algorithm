#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//그래프 - 인접리스트 표현
vector<vector<int>> adj;

//start에서 시작하는 BFS
//각 vertex의 방문 순서 return
vector<int> bfs(int start) {
	//vertex 방문 여부
	vector<bool> discovered(adj.size(), false);
	//방문 vertex 목록을 저장하는 큐
	queue<int> q;
	//vertex 방문 순서(return값)
	vector<int> order;
	
	discovered[start] = true;
	q.push(start);
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		//here를 방문한다
		order.push_back(here);
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i];
			if (!discovered[there]) {
				q.push(there);
				discovered[there] = true;
			}
		}
	}

	return order;
}

// start에서 시작해 BFS를 하면서
// 각 vertex까지 최단 거리와 너비우선탐색 Spanning Tree를 계산한다.
// distance[i] = start~i까지 최단거리
// parent[i] = 너비우선탐색 Spanning Tree에서 i의 부모 노드 번호(root이면 자신)
void bfs2(int start, vector<int>& distance, vector<int>& parent) {
	distance = vector<int>(adj.size(), -1);
	parent = vector<int>(adj.size(), -1);

	queue<int> q;
	distance[start] = 0;
	parent[start] = start;
	q.push(start);
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i];
			if (distance[there] == -1) {
				q.push(there);
				distance[there] = distance[here] + 1;
				parent[there] = here;
			}
		}
	}
}

//v로부터 시작점까지 최단 경로를 계산한다
vector<int> shortestPath(int v, const vector<int>& parent) {
	vector<int> path(1, v);
	while (parent[v] != v) {
		v = parent[v];
		path.push_back(v);
	}
	reverse(path.begin(), path.end());
	return path;
}

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include "State.h"
using namespace std;

typedef map<State, int> StateMap;

//start에서 finish까지 가는 최단경로의 길이를 반환한다.
int bfs(State start, State finish) {
	if (start == finish) return 0;

	//BFS할 큐와 방문 최단경로를 표시하는 map
	queue<State> q;
	StateMap sm;
	q.push(start);
	sm[start] = 0;

	while (!q.empty()) {
		State front = q.front();
		q.pop();
		if (front == finish) return sm[front];

		int current_len = sm[front];
		vector<State> adjacent = front.getAdjacent();
		for (int i = 0; i < adjacent.size(); i++) {
			State next = adjacent[i];
			if (sm.count(next)!=0) continue; //이미 방문한 경우:not 최단경로
			sm[next] = current_len + 1;
			q.push(next);
		}
	}

	//방문할 수 없다
	return -1;
}

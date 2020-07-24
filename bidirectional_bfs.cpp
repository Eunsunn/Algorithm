#include <iostream>
#include <queue>
#include <algorithm>
#include "State.h"
using namespace std;

//게임판의 상태를 표현하는 클래스(puzzle.cpp 참고)
class State;
//x의 부호를 반환한다
int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; };
//x의 절대값을 1 증가시킨다
int incr(int x) { if (x < 0) return x - 1; return x + 1; };
//start에서 finish까지 가는 최단경로의 길이를 반환한다
int bidirectional(State start, State finish) {
	//각 정점까지의 최단경로의 길이를 저장
	map<State, int> c;
	//앞으로 방문할 정점을 저장
	queue<State> q;
	//시작==목표인 경우는 예외처리
	if (start == finish) return 0;
	q.push(start); c[start] = 1;
	q.push(finish); c[finish] = -1;
	while (!q.empty()) {
		State front = q.front();
		q.pop();
		//인접한 상태들을 검사한다.
		vector<State> adjacent = front.getAdjacent();
		for (int i = 0; i < adjacent.size(); i++) {
			map<State, int>::iterator it = c.find(adjacent[i]);
			if (it == c.end()) { //방문하지 않은 상태인 경우
				c[adjacent[i]] = incr(c[front]);
				q.push(adjacent[i]);
			}
			//부호가 다른 경우: 가운데서 만난 경우
			else if (sgn(it->second) != sgn(c[front]))
				return abs(it->second) + abs(c[front]) - 1;
		}
	}

	//답을 찾지 못한 경우
	return -1;
}

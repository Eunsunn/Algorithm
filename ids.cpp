#include <iostream>
#include "State.h"
using namespace std;

//점점 깊어지는 탐색
//Iteratively Deepening Search (IDS)

//15-퍼즐 문제의 상태를 표현하는 클래스
class State;
int best; //최적의 경로 길이

//DFS
void dfs(State here, const State& finish, int steps) { //step:현재까지 경로길이
	//지금까지 구한 최적해보다 더 좋을 가능성이 없으면 중단한다
	if (steps >= best) return;
	//목표 상태에 도달한 경우
	if (here == finish) { best = steps; return; }
	//인접한 상태들을 DFS
	vector<State> adjacent = here.getAdjacent();
	for (int i = 0; i < adjacent.size(); i++)
		dfs(adjacent[i], finish, steps + 1);
}

//점점 깊어지는 탐색
int ids(State start, State finish, int growthStep) {
	for (int limits = 4; ; limits += growthStep) {
		best = limits + 1;
		dfs(start, finish, 0);
		if (best <= limits) return best;
	}
	return -1;
}

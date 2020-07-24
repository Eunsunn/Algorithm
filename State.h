#pragma once
#include <iostream>
#include <vector>
#include <map>
using namespace std;

static const int dir[] = { 1,-1,4,-4 }; //동서남북

//퍼즐 게임판의 상태: NxN 게임판
// row, blank, puzzle 초기화해주기!
class State {
public:
	static int row;
	int blank;
	vector<int> puzzle; //row단위로 인접하게 저장

	//인접한 상태들의 목록을 반환
	vector<State> getAdjacent() const;
	//map에 State를 넣기 위한 비교 연산자
	bool operator < (const State& rhs) const;
	//종료 상태와 비교하기 위한 연산자
	bool operator == (const State& rhs) const {
		return this->puzzle == rhs.puzzle;
	}
};
typedef map<State, int> StateMap;



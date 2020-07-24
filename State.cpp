#include "State.h"

//인접한 상태들의 목록을 반환
vector<State> State::getAdjacent() const {
	vector<State> ret;
	//blank를 동서남북으로 이동한다
	for (int i = 0; i < 4; i++) {
		int temp = blank + dir[i];
		if (temp < 0 || temp >= puzzle.size()) continue;
		State newState; newState.puzzle = vector<int>(this->puzzle.begin(), this->puzzle.end());
		//이동한 blank와 원래 그 자리의 값을 swap
		newState.blank = temp;
		swap(newState.puzzle[this->blank], newState.puzzle[newState.blank]);
		ret.push_back(newState);
	}
	return ret;
}

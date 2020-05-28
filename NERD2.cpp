#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

//현재 다른 점에 지배당하지 않는 점들의 목록을 저장한다
//coords[x] = y
//x값을 기준으로 오름차순 정렬한다
map<int, int> coords;
//새로운 점 (x,y)가 기존의 다른 점들에 지배당하는 지 확인한다
bool isDomiated(int x, int y) {
	//x보다 오른쪽에 있는 점들 중 가장 왼쪽 점
	map<int, int>::iterator it = coords.lower_bound(x);
	//그런 점이 없으면 (x,y)는 지배당하지 않음
	if (it == coords.end()) return false;
	//이점은 x보다 오른쪽에 있는 점 중 가장 위에 있는 점이므로
	//(x,y)가 어느 점에 지배되려면 이 점에도 지배되어야 함
	return y < it->second;
}

//새로운 점 (x,y)에 지배당하는 점들을 트리에서 지운다
void removeDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);
	//(x,y) 왼쪽에 있는 점이 없다!
	if (it == coords.begin()) return;
	--it;
	while (true) {
		//(x,y)바로 왼쪽에 오는 점을 찾는다
		//it가 표시하는 점이 (x,y)에 지배되지 않으면 바로 종료
		if (it->second > y) break;
		//이전 점이 더 없으므로 it만 지우고 종료한다
		if (it == coords.begin()) {
			coords.erase(it);
			break;
		}
		else {
			map<int, int>::iterator jt = it;
			--jt;
			coords.erase(it);
			it = jt;
		}
	}
}

//새 점 (x,y)가 추가되었을 때 coords를 갱신하고,
//다른 점에 지배당하지 않는 점들의 개수를 반환
int registered(int x, int y) {
	//(x,y)가 지배당하는 경우 버린다
	if (isDomiated(x, y)) return coords.size();
	//기존에 있던 점 중 (x,y)에 지배당하는 점들을 지운다
	removeDominated(x, y);
	coords[x] = y;
	return coords.size();
}

int main() {
	int C, N;
	scanf("%d", &C);
	for (int c = 0; c < C; c++) {
		scanf("%d", &N);
		coords.clear();
		int sum = 0;
		for (int i = 0; i < N; i++) {
			int x = 0, y = 0;
			scanf("%d %d", &x, &y);
			sum += registered(x, y);
		}

		printf("%d\n", sum);
	}
	
	return 0;
}

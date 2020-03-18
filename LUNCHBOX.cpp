#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

const unsigned int MAX_N = 10000;
int n, e[MAX_N], m[MAX_N];

int heat() {
	//먹는데 오래 걸리는 순서 -> -후 오름차순 정렬
	vector<pair<int, int>> order;
	for (int i = 0; i < n; i++)
		order.push_back(make_pair(-e[i], i));
	sort(order.begin(), order.end()); //pair의 first에 의해 정렬
	//시간 결정
	int ret = 0, beginEat = 0;
	for (int i = 0; i < n; i++) {
		int box = order[i].second; //box index
		beginEat += m[box]; //데우는 시간 누적
		ret = max(ret, beginEat + e[box]);
	}
	return ret;
}

int main() {
	int C;
	cin >> C;
	for (int c = 0; c < C; c++) {
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> m[i];
		for (int i = 0; i < n; i++)
			cin >> e[i];
		cout << heat() << endl;
	}
}

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 8;

//slow version
int bfs(const vector<int>& perm) {
	int n = perm.size();
	//목표 vertex를 미리 계산
	vector<int> sorted = perm;
	sort(sorted.begin(), sorted.end());
	//방문 목록(큐)와 시작부터 각 정점까지의 거리
	queue<vector<int>> q;
	map<vector<int>, int> distance;
	//시작점을 큐에 넣는다
	q.push(perm);
	distance[perm] = 0;
	//BFS
	while (!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		//도달하면 종료한다
		if (here == sorted) return distance[here];
		int cost = distance[here];
		//도달하지 못한 경우 : 가능한 모든 부분 구간의 뒤집기를 수행
		for (int i = 0; i < n; i++) { //start idx
			for (int j = i + 2; j <= n; j++) { //end idx
				reverse(here.begin() + i, here.begin() + j);
				//기존에 방문하지 않은 경우만 처리한다
				if (distance.count(here) == 0) {
					distance[here] = cost + 1;
					q.push(here);
				}
				reverse(here.begin() + i, here.begin() + j);
			}
		}
	}
	//oopsi~
	return -1;
}


//fast version
map<vector<int>, int> toSort;
//[0, ..., n-1]의 모든 순열에대해 toSort[]를 계산해 저장
void precalc(int n) {
	vector<int> perm(n);
	for (int i = 0; i < n; i++) perm[i] = i;
	queue<vector<int>> q;
	q.push(perm);
	toSort[perm] = 0;
	while (!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		int cost = toSort[here];
		for (int i = 0; i < n; i++) {
			for (int j = i + 2; j<= n; j++) {
				reverse(here.begin() + i, here.begin() + j);
				if (toSort.count(here) == 0) {
					toSort[here] = cost + 1;
					q.push(here);
				}
				reverse(here.begin() + i, here.begin() + j);
			}
		}
	}
}

int solve(const vector<int>& perm) {
	//perm을 [0, ..., n-1]의 순열로 반환한다
	int n = perm.size();
	vector<int> fixed(n);
	for (int i = 0; i < n; i++) {
		int smaller = 0;
		for (int j = 0; j < n; j++) {
			if (perm[j] < perm[i])
				++smaller;
			fixed[i] = smaller;
		}
	}

	//나머지를 채워넣는다
	for (int i = perm.size(); i < MAXN; i++)
		fixed.push_back(i);
	return toSort[fixed];
}

int main() {
	int C, N;
	cin >> C;

	precalc(MAXN);
	for (int c = 0; c < C; c++) {
		cin >> N;

		vector<int> perm;
		for (int n = 0; n < N; n++)
		{
			int temp;
			cin >> temp;
			perm.push_back(temp);
		}
		
		cout << solve(perm) << endl;
	}
}


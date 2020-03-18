#include <iostream>
#include <vector>
#include <set>
using namespace std;

//set: 균형이진트리로 구현된 노드기반 컨테이너, 원소가 자동으로 정렬, 디폴트 오름차순
//multiset: key가 중복될 수 있는 set
//탐색: O(logN)
//lower_bound: 주어진 것보다 크거나 같은 첫 원소 iterator
//upper_bound: 주어진 것보다 큰 첫 원소 iterator
int order(const vector<int>& russian, const vector<int>& korean) {
	int n = russian.size(), wins = 0;
	//선수 레이팅
	multiset<int> ratings(korean.begin(), korean.end());
	for (int rus = 0; rus < n; rus++) {
		//한국 선수가 아예 이길 수 없는 경우
		if (*ratings.rbegin() < russian[rus])
			ratings.erase(ratings.begin());
		else {
			ratings.erase(ratings.lower_bound(russian[rus])); //lower_bound: 주어진 것보다 크거나 같은 첫 원소의 iterator
			wins++;
		}
	}
	return wins;
}

int main() {
	int C, n=0;
	cin >> C;
	for (int c = 0; c < C; c++) {
		cin >> n;
		vector<int> russian(n), korean(n);
		for (int i = 0; i < n; i++)
			cin >> russian[i];
		for (int i = 0; i < n; i++)
			cin >> korean[i];
		cout << order(russian, korean) << endl;
	}
}

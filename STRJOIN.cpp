#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

const int MAX = 100;
int C, n;

int join(multiset<int> str) {
	int ret = 0;
	while (str.size()>1) {
		int temp = 0;
		for (int i = 0; i < 2; i++) {
			temp += (*str.begin());
			str.erase(str.begin());
		}
		ret += temp;
		str.insert(temp);
	}
	return ret;
}

int concat(const vector<int>& lengths) {
	//최초 큐를 선언
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < lengths.size(); i++)
		pq.push(lengths[i]);
	int ret = 0;
	while (pq.size() > 1) {
		int min1 = pq.top(); pq.pop();
		int min2 = pq.top(); pq.pop();
		pq.push(min1 + min2);
		ret += (min1 + min2);
	}
	return ret;
}

int main() {
	cin >> C;
	for (int c = 0; c < C; c++) {
		cin >> n;
		vector<int> arr(n);
		for (int i = 0; i < n; i++)
			cin >> arr[i];
		multiset<int> str(arr.begin(), arr.end());
		cout << join(str) << endl;
	}
}

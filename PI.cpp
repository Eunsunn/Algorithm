#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int INF = 987654321;
string n;
int cache[10002];
int cases;

int classify(int a, int b) {
	string M = n.substr(a, b - a + 1);
	//숫자가 반복되는 경우 난이도 1
	if (M == string(M.size(), M[0])) return 1;
	bool progressive = true;
	for (int i = 0; i < M.size() - 1; i++)
		if (M[i + 1] - M[i] != M[1] - M[0])
			progressive = false;
	//공차가 -1, 1인 등차수열 난이도 2
	if (progressive && abs(M[1] - M[0]) == 1)
		return 2;
	//번갈아 등장하는지 확인
	bool alternating = true;
	for (int i = 0; i < M.size(); i++)
		if (M[i] != M[i % 2])
			alternating = false;
	if (alternating) return 4;
	if (progressive) return 5;
	return 10;
}

int memorize(int begin) {
	if (begin == n.size()) return 0;
	int& ret = cache[begin];
	if (ret != -1) return ret;
	ret = INF;
	for (int L = 3; L <= 5; L++)
		if (begin + L <= n.size())
			ret = min(ret, memorize(begin + L) + classify(begin, begin + L - 1));
	return ret;
}

int main() {
	cin >> cases;
	for (int c = 0; c < cases; c++) {
		cin >> n;
		memset(cache, -1, n.size() * sizeof(int));
		cout << memorize(0) << endl;
	}
}

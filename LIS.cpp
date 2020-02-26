#include <iostream>
#include <algorithm>
using namespace std;

int c, n;
int cache[100], S[100];

int lis2(int start) {
	int& ret = cache[start];
	if (ret != -1) return ret;
	ret = 1;
	for (int next = start + 1; next < n; next++)
		if (S[start] < S[next])
			ret = max(ret, lis2(next) + 1);
	return ret;
}

int main() {
	cin >> c;
	for (int i = 0; i < c; i++) {
		cin >> n;
		for (int j = 0; j < n; j++) {
			cin >> S[j];
			cache[j] = -1;
		}

		int maxLen = 0;
		for (int begin = 0; begin < n; begin++)
			maxLen = max(maxLen, lis2(begin));
		cout << maxLen << endl;
	}
}

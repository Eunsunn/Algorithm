#include <iostream>
#include <algorithm>
using namespace std;

int c;
int n, m;
int A[100], B[100];
int cache[101][101];
const long long NEGINF = numeric_limits<long long>::min();

int jlis(int indexA, int indexB) {
	//메모이제이션
	int& ret = cache[indexA + 1][indexB + 1];
	if (ret != -1) return ret;
	ret = 0;
	long long a = (indexA == -1 ? NEGINF : A[indexA]);
	long long b = (indexB == -1 ? NEGINF : B[indexB]);
	long long maxElement = max(a, b);
	//다음 원소 찾기
	for (int nextA = indexA + 1; nextA < n; nextA++)
		if (maxElement < A[nextA])
			ret = max(ret, jlis(nextA, indexB) + 1);
	for (int nextB = indexB + 1; nextB < m; nextB++)
		if (maxElement < B[nextB])
			ret = max(ret, jlis(indexA, nextB) + 1);
	return ret;
}


int main() {
	cin >> c;
	for (int i = 0; i < c; i++) {
		cin >> n >> m;
		for (int j = 0; j < n; j++)
			cin >> A[j];
		for (int j = 0; j < m; j++)
			cin >> B[j];
		for (int j = 0; j <= n; j++)
			for (int k = 0; k <= m; k++)
				cache[j][k] = -1;

		int maxLen = jlis(-1, -1);
		cout << maxLen << endl;
	}
}


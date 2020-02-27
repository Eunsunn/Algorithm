#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
int map[100][100];
int cache[100][100];
int countCache[100][100];

int path2(int r, int c) {
	//기저사례: 마지막 row
	if (r == n - 1) return map[r][c];
	//메모이제이션
	int& ret = cache[r][c];
	if (ret != -1) return ret;
	return ret = map[r][c] + max(path2(r+1, c), path2(r+1, c+1));
}

int count(int r, int c) {
	//기저사례: 마지막 row
	if (r == n - 1) return 1;
	//메모이제이션
	int& ret = countCache[r][c];
	if (ret != -1) return ret;
	ret = 0;
	if (path2(r + 1, c + 1) >= path2(r + 1, c)) ret += count(r + 1, c + 1);
	if (path2(r + 1, c + 1) <= path2(r + 1, c)) ret += count(r + 1, c);
	return ret;
}
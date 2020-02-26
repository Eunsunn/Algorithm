#include <iostream>
#include <algorithm>
using namespace std;

int cache[100][100];
int map[100][100];
int c, n;

int path(int row, int col) {
	if (row == (n - 1)) return map[row][col];
	int& ret = cache[row][col];
	if (ret != -1) return ret;
	return ret = max(path(row + 1,col), path(row + 1,col + 1)) + map[row][col];
}

void reset() {
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) {
			map[i][j] = -1;
			cache[i][j] = -1;
		}
}

int main() {
	cin >> c;
	for (int i = 0; i < c; i++) {
		cin >> n;
		reset();
		for (int row = 0; row < n; row++)
			for (int col = 0; col <= row; col++)
				cin >> map[row][col];
		
		int ret = path(0, 0);
		cout << ret << endl;
	}
}

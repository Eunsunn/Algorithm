#include <iostream>
#include <algorithm>
using namespace std;

const int EMPTY = -987654321;
int n, board[50];
int cache[50][50];
int play(int left, int right) {
	//기저사례: 모든 카드를 사용했을 때
	if (left > right) return 0;
	int& ret = cache[left][right];
	if (ret != EMPTY) return ret;
	//수를 왼쪽, 오른쪽에서 가져가는 경우
	ret = max(board[left] - play(left + 1, right), board[right] - play(left, right - 1));
	//수를 없애는 경우
	if (right - left + 1 >= 2) {
		ret = max(ret, -play(left + 2, right));
		ret = max(ret, -play(left, right - 2));
	}
	return ret;

}

int main() {
	int test;
	cin >> test;
	for (int c = 0; c < test; c++) {
		for (int i = 0; i < 50; i++)
			for (int j = 0; j < 50; j++)
				cache[i][j] = EMPTY;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> board[i];
		cout << play(0, n - 1) << endl;
	}
}

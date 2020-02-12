#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int test;
int board[20][20];
int height, width;
int white;
int directions[4][2][2] = { {{1, 1},{1, 0}}, {{1, 0},{1, 1}}, {{0, 1},{1, 1}}, {{1, 1},{0, 1}} };//¤¡´ëÄª, ¤¤, ¤¤´ëÄª, ¤¡
int cases;

void input();
void coverCase();

int main() {

	scanf("%d", &test);
	for (int i = 0; i < test; i++) {
		input();
		if (white % 3 != 0) {
			printf("0\n");
			continue;
		}
		cases = 0;
		coverCase();
		printf("%d\n", cases);
	}
}

void input() {
	scanf("%d %d", &height, &width);
	white = 0;
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			char tmp;
			scanf("%c", &tmp);
			if (tmp == '\n')
				scanf("%c", &tmp);
			if (tmp == '#') {
				board[h][w] = 1; //°ËÀº»ö=1
			}
			else {
				board[h][w] = 0;
				white++;
			}
		}
	}
}
bool startPoint(int rowCol[]) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (board[i][j] == 0) {
				rowCol[0] = i;
				rowCol[1] = j;
				return true;
			}
		}
	}
	return false;
}

bool canAddBlock(int dir, int row, int col) {
	int r = row, c = col;
	if (dir == 2) //¤¤´ëÄª ¸ð¾çÀº xÁÂÇ¥ ¼öÁ¤ÇØ¾ßÇÔ
		c--;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if ((r + i) >= height || (c + j) >= width)
				return false;
			if (directions[dir][i][j] == 1 && board[r+i][c+j] == 1)
				return false;
		}
	}
	return true;
}

void addBlock(int dir, int row, int col) {
	int r = row, c = col;
	if (dir == 2)
		c--;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (directions[dir][i][j] == 1)
				board[r + i][c + j] = 1;
		}
	}
}

void delBlock(int dir, int row, int col) {
	int r = row, c = col;
	if (dir == 2)
		c--;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (directions[dir][i][j] == 1)
				board[r + i][c + j] = 0;
		}
	}
}

bool checkFull() {
	bool ret = true;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (board[i][j] == 0) {
				ret = false;
				return ret;
			}
		}
	}
	return ret;
}

void coverCase() {
	if (checkFull()) {
		cases++;
		return;
	}
	int point[2];
	if (!startPoint(point))
		return;

	bool canCover = false;
	for (int i = 0; i < 4; i++) {
		if (canAddBlock(i, point[0], point[1])) {
			canCover = true;
			break;
		}
	}
	if (!canCover)
		return;

	for (int i = 0; i < 4; i++) {
		if (!canAddBlock(i, point[0], point[1]))
			continue;
		addBlock(i, point[0], point[1]);
		coverCase();
		delBlock(i, point[0], point[1]);
	}
}

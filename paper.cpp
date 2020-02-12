#include <iostream>
using namespace std;

int** paper;
int output[3] = { 0, 0, 0 };

void searchPaper(int row, int col , int size) {
	//±âÀú »ç·Ê
	bool same = true;
	int prev = paper[row][col];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (prev != paper[row+i][col+j]) {
				same = false;
				break;
			}
		}
		if (!same)
			break;
	}
	if (same) {
		output[prev + 1]++;
		return;
	}

	//Àç±ÍÈ£Ãâ
	size /= 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			searchPaper(row + size * i, col + size * j, size);
		}
	}
}

int main() {
	int size;

	cin >> size;
	paper = new int* [size];
	for (int i = 0; i < size; i++) {
		paper[i] = new int[size];
		for (int j = 0; j < size; j++)
			scanf("%d", &paper[i][j]);
	}
	
	searchPaper(0, 0, size);
	for (int i = 0; i < 3; i++)
		printf("%d\n", output[i]);
}
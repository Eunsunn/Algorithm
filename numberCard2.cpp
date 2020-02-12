//문제: https://www.acmicpc.net/problem/10816

#include <iostream>
#include <algorithm>
#define MAX 500000
using namespace std;

int lowerBound(int* card, int, int);
int upperBound(int* card, int, int);

int main() {
	int card[MAX];

	int cLen;
	int temp;
	scanf("%d", &cLen);
	for (int i = 0; i < cLen; i++)
		scanf("%d", &card[i]);
	//오름차순 정렬
	sort(card, card+cLen);

	int tLen;
	scanf("%d", &tLen);
	for (int i = 0; i < tLen; i++) {
		scanf("%d", &temp);
		int upper = upperBound(card, temp, cLen);
		int lower = lowerBound(card, temp, cLen);
		if (upper == (cLen - 1) && card[cLen-1] == temp)
			++upper;
		printf("%d ", upper - lower);
	}
}

int lowerBound(int* card, int target, int cLen) {
	int start = 0, end = cLen - 1;
	int mid;
	while (start < end) {
		mid = start + (end - start) / 2;
		if (card[mid] >= target) {
			end = mid;
		}
		else {
			start = mid + 1;
		}
	}
	return end;
}

int upperBound(int* card, int target, int cLen) {
	int start = 0, end = cLen - 1;
	int mid;
	while (start < end) {
		mid = start + (end - start) / 2;
		if (card[mid] > target) {
			end = mid;
		}
		else {
			start = mid + 1;
		}
	}
	return end;
}
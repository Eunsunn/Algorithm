////#define _CRT_SECURE_NO_WARNINGS
////#include <iostream>
////using namespace std;
////
////int testcase;
////int student, pairs;
////int friends[90] = { 0 };
////int pairCase;
////bool selected[10] = { false };
////
////void input();
////void countPairs(int);
////
////int main() {
////	scanf("%d", &testcase);
////	for (int i = 0; i < testcase; i++) {
////		input();
////		for (int j = 0; j < pairs; j++) {
////			countPairs(i);
////		}
////		printf("%d\n", pairCase);
////	}
////}
////
////void input() {
////	//친구쌍 입력받기
////	scanf("%d %d", &student, &pairs);
////	for (int i = 0; i < 2 * pairs; i++)
////		scanf("%d", &friends[i]);
////
////	//선택여부, 경우의 수 초기화
////	for (int i = 0; i < student; i++)
////		selected[i] = false;
////	pairCase = 0;
////}
////
////void countPairs(int idx) {
////	bool selectAll = true;
////	for (int i = 0; i<student; i++) {
////		if (selected[i] == false) {
////			selectAll = false;
////			break;
////		}
////	}
////	if (selectAll) {
////		pairCase++;
////		return;
////	}
////	if (idx > (pairs-1))
////		return;
////	//idx*2번째 pair를 무조건 포함해야함
////	if (selected[friends[idx * 2]] == false && selected[friends[idx * 2 + 1]] == false) {
////		selected[friends[idx * 2]] = selected[friends[idx * 2 + 1]] = true;
////	}
////	else
////		return;
////	//선택되지 않은 pair추가
////	for (int i = idx + 1; i <= pairs; i++) {
////		countPairs(i);
////	}
////	selected[friends[idx * 2]] = selected[friends[idx * 2 + 1]] = false;
////}
//
//#include <iostream>
//
//int n;
//bool areFriends[10][10];
//int countPairings(bool taken[10]) {
//	int firstFree = -1;
//	for (int i = 0; i < n; i++) {
//		if (!taken[i]) {
//			firstFree = i;
//			break;
//		}
//	}
//
//	if (firstFree == -1) return 1;
//	int ret = 0;
//	for (int pairWith = firstFree + 1; pairWith < n; pairWith++) {
//		if (!taken[pairWith] && areFriends[firstFree][pairWith]) {
//			taken[firstFree] = taken[pairWith] = true;
//			ret += countPairings(taken);
//			taken[firstFree] = taken[pairWith] = false;
//		}
//	}
//	return ret;
//}
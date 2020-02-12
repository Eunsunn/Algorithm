//////문제: https://www.acmicpc.net/problem/10816
////
////#include <iostream>
////#include <vector>
////#include <algorithm>
////using namespace std;
////
////int binarySearch(vector<int>, int, int, int);
////int searchRight(vector<int>, int, int);
////int searchLeft(vector<int>, int, int);
////
////int main() {
////	vector<int> card;
////	vector<int> target;
////	
////	int cardNum, tarNum, temp;
////	cin >> cardNum;
////	for (int i = 0; i < cardNum; i++) {
////		cin >> temp;
////		card.push_back(temp);
////	}
////	cin >> tarNum;
////	for (int i = 0; i < tarNum; i++) {
////		cin >> temp;
////		target.push_back(temp);
////	}
////	
////	//오름차순 정렬
////	sort(card.begin(), card.end());
////	//이진탐색
////	for (int i = 0; i < target.size(); i++) {
////		//cout << "----------------------------" << endl;
////		cout << binarySearch(card, target.at(i), 0, card.size() - 1) << " ";
////	}
////		
////}
////
////int binarySearch(vector<int> card, int target, int start, int end) {
////	int count = 0;
////	int mid;
////	while(start< end) {
////		
////		//start, end는 따로 찾아주기
////		if (target == card.at(end)) {
////			count++;
////			count += searchLeft(card, target, end);
////			return count;
////		}
////		if (target == card.at(start)) {
////			count++;
////			count += searchRight(card, target, start);
////			return count;
////		}
////
////		mid = start + (end - start) / 2;
////		//cout << "start, mid, end : " << start << " " << mid << " " << end << endl;
////		if (card.at(mid) == target) {
////			count++;
////			count += searchLeft(card, target, mid);
////			count += searchRight(card, target, mid);
////			return count;
////		}
////		else if (card.at(mid) > target) {
////			end = mid - 1;
////		}
////		else {//card.at(mid)<target
////			start = mid + 1;
////		}
////	}
////	return count;
////}
////
////int searchRight(vector<int> card, int target, int start) {
////	int ret = 0;
////	for (int i = ++start; i < card.size(); i++) {
////		if (card.at(i) != target)
////			return ret;
////		ret++;
////	}
////	return ret;
////}
////int searchLeft(vector<int> card, int target, int start) {
////	int ret = 0;
////	for (int i = --start; i > 0; i--) {
////		if (card.at(i) != target)
////			return ret;
////		ret++;
////	}
////	return ret;
////}
//
//#include <iostream>
//#include <algorithm>
//#define MAX 500000
//using namespace std;
//
//int lowerBound(int* card, int, int);
//int upperBound(int* card, int, int);
//
//int main() {
//	int card[MAX];
//
//	int cLen;
//	int temp;
//	scanf("%d", &cLen);
//	for (int i = 0; i < cLen; i++)
//		scanf("%d", &card[i]);
//	//오름차순 정렬
//	sort(card, card+cLen);
//
//	int tLen;
//	scanf("%d", &tLen);
//	for (int i = 0; i < tLen; i++) {
//		scanf("%d", &temp);
//		int upper = upperBound(card, temp, cLen);
//		int lower = lowerBound(card, temp, cLen);
//		if (upper == (cLen - 1) && card[cLen-1] == temp)
//			++upper;
//		printf("%d ", upper - lower);
//	}
//}
//
//int lowerBound(int* card, int target, int cLen) {
//	int start = 0, end = cLen - 1;
//	int mid;
//	while (start < end) {
//		mid = start + (end - start) / 2;
//		if (card[mid] >= target) {
//			end = mid;
//		}
//		else {
//			start = mid + 1;
//		}
//	}
//	return end;
//}
//
//int upperBound(int* card, int target, int cLen) {
//	int start = 0, end = cLen - 1;
//	int mid;
//	while (start < end) {
//		mid = start + (end - start) / 2;
//		if (card[mid] > target) {
//			end = mid;
//		}
//		else {
//			start = mid + 1;
//		}
//	}
//	return end;
//}
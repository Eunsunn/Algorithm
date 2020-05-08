#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct RNG {
	unsigned seed;
	RNG() : seed(1983) {}
	unsigned next() {
		unsigned ret = seed;
		seed = ((seed * 214013u) + 2531011u);
		return ret % 10000 + 1;
	}
};


////오프라인 알고리즘
//int simple(const vector<int>& signals, int k) {
//	int ret = 0;
//	for (int head = 0; head < signals.size(); head++) {
//		int sum = 0;
//		for (int tail = head; tail < signals.size(); tail++) {
//			//합=sum(head, tail)
//			sum += signals[tail];
//			if (sum == k) ret++;
//			if (sum >= k) break;
//		}
//	}
//	return ret;
//}

//int opt(const vector<int>& signals, int k) {
//	int ret = 0;
//	int head = 0, tail = 0;
//	int sum = 0;
//	while (tail < signals.size()) {
//		if (sum < k) {
//			sum += signals[tail];
//			tail++;
//		}
//		else if (sum == k) {
//			sum -= signals[head];
//			head++;
//			ret++;
//		}
//		else {
//			sum -= signals[head];
//			head++;
//		}
//	}
//}

//int optimized(const vector<int>& signals, int k) {
//	int ret = 0, tail = 0, rangeSum = signals[0];
//	for (int head = 0; head < signals.size(); head++) {
//		//rangeSum이 k이상인 구간까지 tail을 옮긴다
//		while (rangeSum < k && tail + 1 < signals.size())
//			rangeSum += signals[++tail];
//		if (rangeSum == k)
//			ret++;
//
//		//이제 signal[head]는 구간에서 빠진다
//		rangeSum -= signals[head];
//	}
//	return ret;
//}

//온라인 알고리즘
int countRanges(int k, int n) {
	RNG rng; //신호값을 생성하는 난수 생성기
	queue<int> range;//현재 구간에 들어있는 숫자들을 생성하는 큐
	int ret = 0, rangeSum = 0;
	for (int i = 0; i < n; i++) {
		//구간에 숫자를 추가한다
		int newSignal = rng.next();
		rangeSum += newSignal;
		range.push(newSignal);

		//구간합이 k를 초과하는 동안 구간에서 숫자를 뺀다
		while (rangeSum > k) {
			rangeSum -= range.front();
			range.pop();
		}

		if (rangeSum == k) ret++;
	}
	return ret;
}

int main() {
	int C;
	cin >> C;
	for (int c = 0; c < C; c++) {
		int k, n;
		cin >> k >> n;
		cout << countRanges(k, n) << endl;
	}
}

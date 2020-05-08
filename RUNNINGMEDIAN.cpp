#include <iostream>
#include <queue>
using namespace std;

struct RNG {
	int seed, a, b;
	RNG(int _a, int _b):a(_a), b(_b), seed(1983){}
	int next() {
		int ret = seed;
		seed = ((seed * (long long)a) + b) % 20090711;
		return ret;
	}
};

int runningMedian(int n, RNG rng) {
	priority_queue<int, vector<int>, less<int>> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;
	int ret = 0;
	//반복문 불변식
	//1. maxHeap의 크기는 minHeap의 크기와 같거나 1 더 크다.
	//2. maxHeap.top()<=minHeap.top()
	for (int cnt = 1; cnt <= n; cnt++) {
		//1번 불변식을 만족시킨다.
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());
		//2번 불변식이 깨진 경우 복구
		if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()) {
			int a = maxHeap.top(), b = minHeap.top();
			maxHeap.pop(); minHeap.pop();
			maxHeap.push(b);
			minHeap.push(a);
		}
		ret = (ret + maxHeap.top()) % 20090711;
	}
	return ret;
}

int main() {
	int C;
	cin >> C;
	for (int c = 0; c < C; c++) {
		int n, a, b;
		cin >> n >> a >> b;
		RNG rng(a, b);
		
		int ret = runningMedian(n, rng);
		cout << ret << endl;
	}
}

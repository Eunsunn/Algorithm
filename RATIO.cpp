#include <iostream>
#include <cmath>
using namespace std;

long long N, M, C;

//f(x): (M+x)/(N+x) * 100 - 단조증가함수
long long prob(long long x) {
	return (M + x)*100 / (N + x);
}

int bisection() {
	long long lo = 0, hi = 2e9;
	long long flo = prob(lo), fhi = prob(hi);
	//기저사례: 20억번 내에 없는 경우
	if (flo == fhi)
		return -1;
	//반복문 불변식
	//lo게임 이기면 승률은 변하지 않는다
	//hi게임 이기면 승률을 변한다
	while (lo + 1 < hi) {
		long long mid = (lo + hi) / 2;
		if (prob(0) == prob(mid))
			lo = mid;
		else
			hi = mid;
	}
	return hi;
}

int main() {
	cin >> C;
	for (int c = 0; c < C; c++) {
		cin >> N >> M;
		cout << bisection() << endl;
	}
}

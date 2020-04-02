#include <iostream>
using namespace std;

//익명의 함수
double f(double x);
//이분법 예제 구현
double bisection(double lo, double hi) {
	//반복문 불변식 강제
	if (f(lo) > 0)
		swap(lo, hi);
	//반복문 불변식: f(lo)<=0<f(hi)
	while (fabs(hi - lo) > 2e-7) { //절대오차
		double mid = (lo + hi) / 2;
		double fmid = f(mid);
		if (fmid <= 0)
			lo = mid;
		else
			hi = mid;
	}
	return (lo + hi) / 2;
}

//영원히 종료되지 않는 절대오차 이분법
void infiniteBisection() {
	double lo = 123456123456.1234588623046875;
	double hi = 123456123456.1234734184739189;
	while (fabs(hi - lo) > 2e-7)
		hi = (lo + hi) / 2.0;
	printf("finished");
}

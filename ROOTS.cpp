//단변수 다항 방정식의 해를 이분법으로 찾기
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

//단일변수 다항식 p의 계수가 주어질 때 미분한 결과 p'의 계수를 반환
vector<double> differentiate(const vector<double>& poly) {
	vector<double> diff;
	for (int i = 0; i < poly.size(); i++) {
		int d = poly[i];
		d *= (poly.size() - i - 1);
		diff.push_back(d);
	}
	return diff;
}

//1차 혹은 2차 방정식 풀기: 최고차항 계수가 0이 아님
vector<double> solveNaive(const vector<double>& poly) {
	vector<double> root;
	//1차
	if (poly.size() == 2) {
		root.push_back(-(poly[0] / poly[1]));
	}
	//2차
	else if (poly.size() == 3) {
		double a = poly[0], b = poly[1], c = poly[2];
		double r1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
		double r2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		root.push_back(r1);
		root.push_back(r2);
	}
	return root;
}

//다항식 f(x)의 계수 poly가 주어질 때, f(x0)을 반환
double evaluate(const vector<double>& poly, double x0) {
	double out = 0;
	for (int i = 0; i < poly.size(); i++) {
		out += pow(poly[i], i);
	}
	return out;
}

//방정식의 해의 절대 값은 L이하여야 한다
const double L = 25;
//방정식 sum(poly[i]*x^i)=0의 근을 반환
vector<double> solve(const vector<double>& poly) {
	int n = poly.size() - 1;
	//기저 사례: 2차 이하의 방정식들은 풀 수 있다
	if (n <= 2) return solveNaive(poly);
	//방정식을 미분해 n-1차 방정식을 얻는다
	vector<double> derivative = differentiate(poly);
	vector<double> sols = solve(derivative);
	//극점들 사이를 검사하며 근을 확인한다
	sols.insert(sols.begin(), -L - 1); //양쪽 끝의 근 찾기위해
	sols.insert(sols.end(), L + 1); //최소, 최대값을 넣어준다
	vector<double> ret;
	for (int i = 0; i + 1 < sols.size(); i++) {
		double x1 = sols[i], x2 = sols[i + 1];
		double y1 = evaluate(poly, x1), y2 = evaluate(poly, x2);
		//f(x1)*f(x2): 사이에 답이 없음
		if (y1 * y2 > 0) continue;
		//불변조건:f(x1)<=0<f(x2)
		if (y1 > y2) { swap(y1, y2); swap(x1, x2); }
		//이분법을 사용해 근을 찾자
		for (int iter = 0; iter < 100; iter++) {
			double mx = (x1 + x2) / 2;
			double my = evaluate(poly, mx);
			if (y1 * my > 0) {
				y1 = my;
				x1 = mx;
			}
			else {
				y2 = my;
				x2 = mx;
			}
		}
		ret.push_back((x1 + x1) / 2);
	}
	sort(ret.begin(), ret.end());
	return ret;
}

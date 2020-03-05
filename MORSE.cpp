#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

//오버플로우를 막을 MAX값
const int M = 1000000000 + 100;
int skip; //건너뛸 개수=k-1
int bino[201][201]; //이항계수

////완전탐색
//void generate(int n, int m, string s) {
//	//기저사례: n=m=0 (더이상 사용할 부호가 없는 경우)
//	if (n == 0 && m == 0) {
//		cout << s << endl;
//		return;
//	}
//	//장점, 단점 순서 탐색
//	if (n > 0) generate(n - 1, m, s + "-");
//	if (m > 0) generate(n, m - 1, s + "o");
//}
//
////전역변수 skip이 k-1로 초기화
////k-1개 건너뛰기
//void generate2(int n, int m, string s) {
//	//기저사례: 이미 다른 경우에서 k번째 출력한 경우
//	if (skip < 0) return;
//	//기저사례: n=m=0
//	if (n == 0 && m == 0) {
//		if (skip == 0) cout << s << endl;
//		--skip;
//		return;
//	}
//	if (n > 0) generate2(n - 1, m, s + "-");
//	if (m > 0) generate2(n, m - 1, s + "o");
//}

//이항계수로 건너뛰기
void calcBino() {
	memset(bino, 0, sizeof(bino));
	for (int i = 0; i <= 200; i++) {
		bino[i][0] = bino[i][i] = 1;
		for (int j = 1; j < i; j++)
			bino[i][j] = min(M, bino[i - 1][j - 1] + bino[i - 1][j]); //오버플로우 방지
	}
}
//n개의 '-'(장음), m개의 'o'(단음)
void generate3(int n, int m, string s) {
	if (skip < 0) return;
	if (n == 0 && m == 0) {
		if (skip == 0) 
			cout << s << endl;
		skip--;
		return;
	}
	//n+m개 모든 경우의 수를 건너뛸 수 있으면
	if (bino[n + m][n] <= skip) {
		skip -= bino[n + m][n];
		return;
	}
	//건너뛸 수 없으면
	if (n > 0) generate3(n - 1, m, s + "-");
	if (m > 0) generate3(n, m - 1, s + "o");
}
////n개의 '-', m개의 'o' 신호, skip개를 건너뛰어야 함
//string kth(int n, int m, int skip) {
//	//'-'을 다 쓴 경우
//	if (n == 0) return string(m, 'o');
//	//'-'이 첫번째인 경우를 뛰어넘을 수 없으면
//	if (skip < bino[n + m - 1][n - 1])
//		return "-" + kth(n - 1, m, skip);
//	//'-'이 첫번째인 경우를 뛰어넘을 수 있으면
//	return "o" + kth(n, m - 1, skip - bino[n + m - 1][n - 1]);
//}

int main() {
	int C;
	cin >> C;
	calcBino();
	for (int c = 0; c < C; c++) {
		int l, s, k;
		string result;
		cin >> l >> s >> k;
		skip = k - 1;
		generate3(l, s, result);
	}

}

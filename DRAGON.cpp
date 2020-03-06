#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 1000000000 + 1;

int length[51];
//length[i]=X와 Y를 i번 치환한 길이
void precalc() {
	length[0] = 1;
	for (int i = 1; i <= 50; i++)
		length[i] = min(MAX, length[i - 1] * 2 + 2);
}

const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";

char expand(const string& dragonCurve, int generations, int skip) {
	//기저사례
	if (generations == 0) {
		//확장할 수 없는데 뛰어넘어야 하는 경우-종료
		if (skip > dragonCurve.size())
			exit(-1);
		return dragonCurve[skip];
	}
	for (int i = 0; i < dragonCurve.size(); i++) {
		//문자열이 확장되는 경우
		if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y') {
			//뛰어넘는 경우
			if (skip >= length[generations])
				skip -= length[generations];
			//뛰어넘지 못하는 경우-확장
			else if (dragonCurve[i] == 'X')
				return expand(EXPAND_X, generations - 1, skip);
			else
				return expand(EXPAND_Y, generations - 1, skip);
		}
		//확장되지 않고 건너뛰는 경우
		else if (skip > 0)
			--skip;
		//답을 찾은 경우
		else
			return dragonCurve[i];
	}
	return '#'; //실행되지 않음
}

int main() {
	int C;
	cin >> C;
	precalc();
	for (int c = 0; c < C; c++) {
		int n, p, l;
		cin >> n >> p >> l;
		for (int i = 0; i < l; i++) {
			cout << expand("FX", n, p + i-1);
		}
		cout << endl;
	}
}

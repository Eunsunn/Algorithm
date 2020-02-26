#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <list>
using namespace std;

//-1:계산안함, 1:대응됨, 0:대응안됨
int cache[101][101] = { -1, };
string W, S;
int c, n;

int matchMemoized(int w, int s) {
	int& ret = cache[w][s];
	if (ret != -1) return ret;
	if (w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s]))
		return ret = matchMemoized(w + 1, s + 1);
	if (w == W.size()) return ret = (s == S.size());
	if (W[w] == '*') {
		if (matchMemoized(w + 1, s) || (s < S.size() && matchMemoized(w, s + 1)))
			return ret = 1;
	}
	return ret = 0;
}

void reset() {
	for (int w = 0; w <= W.size(); w++)
		for (int s = 0; s <= S.size(); s++)
			cache[w][s] = -1;
}

int main() {
	scanf("%d", &c);
	for (int i = 0; i < c; i++) {
		cin >> W;
		cin >> n;
		list<string> Ss;
		for (int j = 0; j < n; j++) {
			cin >> S;
			reset();
			if (matchMemoized(0, 0))
				Ss.push_back(S);
		}
		Ss.sort();
		list<string>::iterator it = Ss.begin();
		for (; it != Ss.end(); it++)
			cout << *it << endl;
	}
}

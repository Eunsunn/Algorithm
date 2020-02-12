//#include <iostream>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//vector<int> h;
//
//int solve(int left, int right) {
//	//기저사례
//	if (left == right) return h[left];
//	int mid = (left + right) / 2;
//	//양쪽 분할
//	int ret = max(solve(left, mid), solve(mid + 1, right));
//	//가운데 걸치는 사례
//	int lo = mid, hi = mid + 1;
//	int height = min(h[lo], h[hi]);
//	ret = max(ret, height * 2); //height*2: 경계에 인접한 울타리 2개 선택
//	//높이가 큰걸 선택하면서 가운데 걸치는 사례 완전탐색
//	while (left<lo || hi<right) {
//		if (hi < right && (lo == left || h[lo - 1] < h[hi + 1])) { //오른쪽선택
//			hi++;
//			height = min(height, h[hi]);
//		}
//		else { //왼쪽선택
//			lo--;
//			height = min(height, h[lo]);
//		}
//		ret = max(ret, height * (hi - lo + 1));
//	}
//	return ret;
//}
//
//int main() {
//	int cases;
//	int fenceSize;
//	cin >> cases;
//	for (int i = 0; i < cases; i++) {
//		cin >> fenceSize;
//		for (int j = 0; j < fenceSize; j++) {
//			int tmp;
//			cin >> tmp;
//			h.push_back(tmp);
//		}
//		cout << solve(0, fenceSize - 1) << endl;
//		h.clear();
//	}
//}
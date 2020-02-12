//#include <iostream>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//vector<int> h;
//
//int solve(int left, int right) {
//	//�������
//	if (left == right) return h[left];
//	int mid = (left + right) / 2;
//	//���� ����
//	int ret = max(solve(left, mid), solve(mid + 1, right));
//	//��� ��ġ�� ���
//	int lo = mid, hi = mid + 1;
//	int height = min(h[lo], h[hi]);
//	ret = max(ret, height * 2); //height*2: ��迡 ������ ��Ÿ�� 2�� ����
//	//���̰� ū�� �����ϸ鼭 ��� ��ġ�� ��� ����Ž��
//	while (left<lo || hi<right) {
//		if (hi < right && (lo == left || h[lo - 1] < h[hi + 1])) { //�����ʼ���
//			hi++;
//			height = min(height, h[hi]);
//		}
//		else { //���ʼ���
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
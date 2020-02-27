#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 1000000007;
int cases;
int n;
int cache[101];
 
//���1: ��Ī Ÿ�� count
int tiling(int width) {
	//�������
	if (width <= 1) return 1;
	int& ret = cache[width];
	if (ret != -1) return ret;
	return ret = (tiling(width - 1) + tiling(width - 2)) % MOD;
}

int asymtiling() {
	if (n % 2 == 1)
		return (tiling(n) - tiling(n / 2) + MOD) % MOD;
	int ret = tiling(n);
	ret = (ret - tiling(n / 2) + MOD) % MOD;
	ret = (ret - tiling(n / 2 - 1) + MOD) % MOD;
	return ret;
}

//���2: ���Ī Ÿ�� count
int cache2[101];
int assymmertic2(int width) {
	//�������
	if (width <= 2) return 0;
	//�޸������̼�
	int& ret = cache2[width];
	if (ret != -1) return ret;
	ret = assymmertic2(width - 2) % MOD;
	ret = (ret + assymmertic2(width - 4)) % MOD;
	ret = (ret + tiling(width - 3)) % MOD;
	ret = (ret + tiling(width - 3)) % MOD;
	return ret;
}

int main() {
	cin >> cases;
	for (int c = 0; c < cases; c++) {
		cin >> n;
		memset(cache, -1, sizeof(cache));
		cout << asymtiling() << endl;
	}
}



#include <iostream>
using namespace std;

const int MOD = 100000007;
int cache[101]; //tiling(0)~tiling(100) ����
int tiling(int width) {
	//�������: 0�Ǵ� 1�϶�
	if (width <= 1) return 1;
	//�޸������̼�
	int& ret = cache[width];
	if (ret != -1) return ret;
	return ret = (tiling(width - 1) + tiling(width - 2)) % MOD;
}
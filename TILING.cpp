#include <iostream>
using namespace std;

const int MOD = 100000007;
int cache[101]; //tiling(0)~tiling(100) 저장
int tiling(int width) {
	//기저사례: 0또는 1일때
	if (width <= 1) return 1;
	//메모이제이션
	int& ret = cache[width];
	if (ret != -1) return ret;
	return ret = (tiling(width - 1) + tiling(width - 2)) % MOD;
}
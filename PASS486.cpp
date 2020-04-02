#include <iostream>
#include <cstring>	//memset
#include <cmath>
using namespace std;

const int TM = 1000*1000*10;
//minFactor[i]=i의 가장 작은 소인수(소수인 경우 자기자신)
int minFactor[TM + 1];
//minFactorPower[i]=i의 소인수 분해에는 minFactor[i]의 몇승이 포함되어 있는가?
int minFactorPower[TM + 1];
//factors[i]=i가 가진 약수의 수
int factors[TM + 1];

void eratosthenes() {
	//0과 1은 예외처리
	minFactor[0] = minFactor[1] = -1;
	for (int i = 2; i <= TM; i++)
		minFactor[i] = i;

	int sqrtn = (int)sqrt(TM);
	for (int i = 2; i <= sqrtn; i++) {
		if(minFactor[i]==i){
			for (int j = i * i; j <= TM; j += i)
				if (minFactor[j] == j)
					minFactor[j] = i;
		}
	}
}


void getFactorsSmart() {
	factors[1] = 1;
	for (int n = 2; n <= TM; n++) {
		//소수인 경우 약수가 두 개 밖에 없다
		if (minFactor[n] == n) {
			minFactorPower[n] = 1;
			factors[n] = 2;
		}
		//소수가 아닌 경우, 가장 작은 소인수로 나눈 수(m)의
		//약수의 수를 사용해 n의 약수를 찾는다
		else {
			int p = minFactor[n];
			int m = n / p;
			//m이 p로 나누어 떨어지지 않는 경우
			if (p != minFactor[m])
				minFactorPower[n] = 1;
			else
				minFactorPower[n] = minFactorPower[m] + 1;
			int a = minFactorPower[n];
			factors[n] = (factors[m] / a) * (a + 1);
		}
	}
}

//1천만 이하의 모든 수의 약수를 계산하는 단순 알고리즘
//TM이 커지면 시간복잡도가 O(nlogn)에 수렴
void getFactorsBrute() {
	memset(factors, 0, sizeof(factors));
	for (int div = 1; div <= TM; div++) {
		for (int multiple = div; multiple <= TM; multiple += div)
			factors[multiple] += 1;
	}
}

int main() {
	int C, n, lo, hi;
	cin >> C;
	eratosthenes();
	getFactorsSmart();

	for (int c = 0; c < C; c++) {
		cin >> n >> lo >> hi;
		int count = 0;
		for (int i = lo; i <= hi; i++)
			if (factors[i] == n)
				count++;
		cout << count << endl;
	}
}

#include <iostream>
#include <vector>
#include <cstring>	//memset
using namespace std;

//O(sqrt(n)) 시간에 소수인지 판별
bool Prime(int n) {
	//예외처리: 1과 2
	if (n <= 1) return false;
	if (n == 2) return true;
	//2를 제외한 모든 짝수는 합성수
	if (n % 2 == 0) return false;
	//3이상의 홀수로 나누자
	int sqrtn = int(sqrt(n));
	for (int div = 3; div <= sqrtn; div += 2)
		if (n % div == 0)
			return false;
	return true;
}

//정수 n을 소인수분해
vector<int> factorSimple(int n) {
	vector<int> ret;
	int sqrtn = int(sqrt(n));
	for (int div = 2; div <= sqrtn; div++) {
		while (n % div == 0) {
			n /= div;
			ret.push_back(div); //중복처리는 안됨
		}
	}
	if (n > 1) ret.push_back(n);
	return ret;
}


//에라토스테네스의 체
int n;
const int MAX_N = 2000;
bool isPrime[MAX_N+1];
//함수를 종료한 뒤 isPrime[i]=i가 소수인가?
//최적화1: 지워지지 않은 수를 sqrt(n)까지 탐색
//최적화2: 지울 수를 i*i에서 시작
void eratosthenes() {
	//bool은 1byte므로 1로 채워짐
	memset(isPrime, 1, sizeof(isPrime));
	//1은 항상 예외처리
	isPrime[0] = isPrime[1] = false;
	int sqrtn = int(sqrt(n));
	for (int i = 2; i < sqrtn; i++) {
		//지워지지 않은 수라면
		if (isPrime[i])
			for (int j = i * i; j <= n; j += i)
				isPrime[j] = false;
	}
}

//에라토스테네스의 체를 이용한 빠른 소인수분해
//minFactor[i]=i의 가장 작은 소인수(i가 소수인 경우 자신)
int minFactor[MAX_N];
//에라토스테네스의 체를 수행하면서 소인수분해를 위한 정보도 저장
void eratosthenes2() {
	//1은 꼭 예외처리!!!!
	minFactor[0] = minFactor[1] = -1;
	//모든 숫자를 처음에는 소수로 표시해둔다
	for (int i = 2; i < n; i++)
		minFactor[i] = i;
	//에라토스테네스의 체
	int sqrtn = int(sqrt(n));
	for (int i = 2; i <= sqrtn; i++) {
		//소수인 경우
		if (minFactor[i] = i) {
			for (int j = i * i; j <= n; j += i)
				//아직 약수를 본 적 없는 숫자인 경우 i를 써둔다
				if (minFactor[j] == j)
					minFactor[j] = i;
		}
	}		
}
//2 이상의 자연수 n을 소인수분해한 결과를 반환한다
vector<int> factor(int n) {
	vector<int> ret;
	while (n > 1) {
		ret.push_back(minFactor[n]);
		n /= minFactor[n];
	}
	return ret;
}

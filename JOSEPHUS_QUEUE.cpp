#include <iostream>
#include <queue>
using namespace std;

int C, N, K;

int main() {
	cin >> C;
	for (int i = 0; i < C; i++) {
		cin >> N >> K;
		queue<int> q;
		for (int j = 1; j <= N; j++)
			q.push(j);

		while (q.size() > 2) {
			//맨 앞 병사를 지우고
			q.pop();
			//다음 죽을 병사 전까지 큐의 뒤로 옮긴다
			for (int pop = 0; pop < K-1; pop++) {
				int temp = q.front();
				q.pop();
				q.push(temp);
			}
		}
		
		//출력
		int val1 = q.front();
		q.pop();
		int val2 = q.front();
		if (val1 > val2) swap(val1, val2);
		cout << val1 << " " << val2 << endl;
	}
}

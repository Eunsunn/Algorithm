#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

int solveStack();

//판자의 높이를 저장하는 배열
vector<int> h;

int main() {
	int C, N;
	cin >> C;
	for (int c = 0; c < C; c++) {
		cin >> N;
		h.clear();
		for (int i = 0; i < N; i++)
		{
			int temp;
			cin >> temp;
			h.push_back(temp);
		}

		cout << solveStack() << endl;
	}
}

//스택을 사용한 O(n) 해법
int solveStack() {
	//남아있는 판자들의 위치를 저장
	stack<int> remaining;
	h.push_back(0);//맨 오른쪽에 높이가 0인 가상의 판자 추가
	int ret = 0;
	for (int i = 0; i < h.size(); i++) {
		//남아있는 판자들 중 오른쪽 끝 판자가 h[i]보다 높다면
		//이 판자의 최대 사각형은 i에서 끝난다
		while (!remaining.empty() && h[remaining.top()] >= h[i]) {
			int j = remaining.top();
			remaining.pop();
			int width = -1;
			//j번째 판자 왼쪽에 판자가 하나도 안남아 있으면 left[j]=-1,
			//아닌 경우 left[j]=남아 있는 판자 중 가장 오른쪽에 있는 판자의 번호
			if (remaining.empty())
				width = i;
			else
				width = (i - remaining.top() - 1);
			ret = max(ret, h[j] * width);
		}
		remaining.push(i);
	}
	return ret;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//vector slicing : O(n)
vector<int> slice(const vector<int>& v, int a, int b) {
	return vector<int>(v.begin() + a, v.begin() + b);
}

//트리의 전위탐색 결과와 중위탐색 결과가 주어질 때 후위탐색 결과를 출력
void printPostOrder(const vector<int>& preorder, const vector<int>& inorder) {
	//트리 노드 수
	const int N = preorder.size();
	
	//기저사례: 텅 빈 트리
	if (preorder.empty()) return;
	//루트 노드: 전위탐색 결과의 첫번째
	const int root = preorder[0];
	//왼쪽 subtree크기: 중위탐색에서 루트노드 위치 이전까지 왼쪽 subtree
	const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
	//오른쪽 subtree크기: 전체 개수-(왼쪽 subtree개수)-1(root)
	const int R = N - 1 - L;
	//왼쪽과 오른쪽 서브트리의 순회 결과를 출력
	printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
	printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
	//후위순위: root를 가장 마지막에 출력
	cout << root << " ";
}

int main() {
	int C, N;
	cin >> C;
	for (int c = 0; c < C; c++) {
		cin >> N;
		vector<int> preorder(N);
		vector<int> inorder(N);
		for (int i = 0; i < N; i++)
			cin >> preorder[i];
		for (int i = 0; i < N; i++)
			cin >> inorder[i];

		printPostOrder(preorder, inorder);
		cout << endl;
	}
}

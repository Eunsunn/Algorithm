#include <iostream>
#include <vector>
using namespace std;

//BST 구조체
struct Node {
	int val;
	struct Node* left;
	struct Node* right;
};

Node* makeTree(int, int, int);
void printPostOrder(struct Node*);

vector<int> preorder;
vector<int> inorder;

int main() {
	int C, N;
	cin >> C;
	for (int c = 0; c < C; c++) {
		cin >> N;
		preorder.clear();
		inorder.clear();
		
		int temp;
		for (int i = 0; i < N; i++)
		{
			cin >> temp;
			preorder.push_back(temp);
		}
		for (int i = 0; i < N; i++)
		{
			cin >> temp;
			inorder.push_back(temp);
		}

		Node* root = makeTree(0, 0, N);
		printPostOrder(root);
		cout << endl;
	}
}

Node* makeTree(int preStart, int inStart, int size) {
	struct Node* root = new Node();
	root->val = preorder[preStart];

	//중순위에서 root노드 위치를 찾아서 left subtree size 계산
	int in_idx = -1;
	for (int i = 0; i < size; i++)
		if (inorder[inStart + i] == root->val)
		{
			in_idx = inStart + i;
			break;
		}
	int leftSize = in_idx - inStart;
	int rightSize = size - leftSize - 1;

	//left subtree, right subtree 만들기
	struct Node* left = nullptr;
	if(leftSize) left = makeTree(preStart + 1, inStart, leftSize);
	struct Node* right = nullptr;
	if(rightSize) right = makeTree(preStart + 1 + leftSize, in_idx + 1, rightSize);

	//root와 child 이어주기
	root->left = left;
	root->right = right;

	return root;
}

void printPostOrder(struct Node* root) {
	if (root == nullptr) return;
	printPostOrder(root->left);
	printPostOrder(root->right);
	cout << root->val << " ";
}

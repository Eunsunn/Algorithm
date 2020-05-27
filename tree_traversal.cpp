#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//트리 구조체
struct TreeNode {
	string label;
	TreeNode* parent;
	vector<TreeNode*> children;
};

//트리 순회(모든 값 출력하기)
void printLabels(TreeNode* root) {
	//루트에 저장된 값 출력
	cout << root->label << endl;
	//각 자손들을 루트로 하는 서브트리에 포함된 값들을 재귀적으로 출력
	for (int i = 0; i < root->children.size(); i++)
		printLabels(root->children[i]);
}

//트리 순회(트리 높이 구하기)
int height(TreeNode* root) {
	int h = 0;
	for (int i = 0; i < root->children.size(); i++)
		h = max(h, 1 + height(root->children[i]));
	return h;
}

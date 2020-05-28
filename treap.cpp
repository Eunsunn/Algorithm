#include <iostream>
using namespace std;

//트립의 한 노드를 저장
struct Node {
	//노드에 저장된 값
	int key;
	//이 노드의 우선순위(priority)
	//이 노드를 루트로하는 서브트리의 크기(size)
	int priority, size;
	//두 자식 노드 포인터
	struct Node* left, * right;
	//생성자에서 난수 우선순위를 생성하고, size와 left, right 초기화
	Node(const int& _key) : key(_key), priority(rand()),
		size(1), left(NULL), right(NULL) {}
	void setLeft(struct Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(struct Node* newRight) { right = newRight; calcSize(); }
	//size 멤버를 갱신
	void calcSize() {
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};

//트립의 노드 추가와 트랩 쪼개기 연산 구현
typedef pair<Node*, Node*> NodePair;
//root를 루트로하는 트립을 key미만의 갑소가 이상의 값을 갖는
//두개의 트립으로 분리한다.
NodePair split(struct Node* root, int key){
	if (root == NULL) return NodePair(NULL, NULL);
	//루트가 key 미만이면 오른쪽 서브트리를 쪼갠다
	if (root->key < key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	//루트가 key 이상이면 왼쪽 서브트리를 쪼갠다
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}
//root를 루트로 하는 트립에 새 노드 node를 삽입한 뒤 결과 트립의
//루트를 반환한다
struct Node* insert(struct Node* root, struct Node* node) {
	if (root == NULL) return node;
	//node의 우선순위가 높은 경우 root를 대체한다.
	//root의 subtree를 적당하게 반으로 잘라 node의 subtree로 사용한다
	if (root->priority < node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	//node의 우선순위가 낮고 값이 root보다 작으면
	//root의 왼쪽 subtree에 삽입한다
	else if (node->key < root->key) {
		root->setLeft(insert(root->left, node));
	}
	else {
		root->setRight(insert(root->right, node));
	}
	return root;
}

//a와 b가 두개의 트립이고, max(a) < min(b)일 때(value) 이 둘을 합친다
struct Node* merge(struct Node* a, struct Node* b) {
	if (a == NULL) return b;
	if (b == NULL) return a;
	if (a->priority < b->priority) {
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}
//root를 루트로 하는 트립에서 key를 지우고 결과 트립의 루트를 반환한다
struct Node* erase(struct Node* root, int key) {
	if (root == NULL) return root;
	//root를 지우고 양 서브트리를 합친 뒤 반환한다
	if (root->key == key) {
		struct Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	if (key < root->key)
		root->setLeft(erase(root->left, key));
	else
		root->setRight(erase(root->right, key));
	return root;
}

//root를 루트로 하는 트리 중 k번째 원소를 반환한다
struct Node* kth(struct Node* root, int k) {
	//왼쪽 서브트리의 크기를 계산한다
	int leftSize = 0;
	if (root->left != NULL) leftSize = root->left->size;
	if (k <= leftSize) return kth(root->left, k);
	if (k == leftSize + 1) return root;
	return kth(root->right, k-leftSize-1);
}

//key보다 작은 키값의 수를 반환한다
int countLessThan(struct Node* root, int key) {
	if (root == NULL) return 0;
	if (root->key >= key)
		return countLessThan(root->left, key);
	int ls = (root->left ? root->left->size : 0);
	return ls + 1 + countLessThan(root->right, key);
}

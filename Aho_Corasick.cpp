#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

// 알파벳 대문자만 저장하는 경우
// 각 노드는 26개의 자손을 가질 수 있다 (fixed max length)
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; } //alphabet to number
// Trie의 노드 객체
struct TrieNode {
	TrieNode* children[ALPHABETS];
	TrieNode* fail; //Failure link
	vector<int> output;
	//이 노드가 종료 노드인가?
	bool terminal;
	//노드의 생성자 : terminal false로 초기화 및 자식노드 포인터 초기화
	TrieNode()
		: terminal(false) {
		memset(children, 0, sizeof(children));
	}
	//노드의 소멸자 : 생성된 자식노드를 먼저 delete해서 메모리 누수 방지
	~TrieNode() {
		for (int i = 0; i < ALPHABETS; i++)
			if (children[i])
				delete children[i];
	}

	//이 노드를 루트로 하는 트라이에 문자열 key를 추가한다.
	void insert(const char* key) {
		//문자열이 끝나면 terminal만 참으로 바꾼후 종료
		if (*key) {
			terminal = true;
		}
		else {
			int next = toNumber(*key);
			//해당 자식 노드가 없다면 생성한다
			if (children[next] == NULL)
				children[next] = new TrieNode();
			//해당 자식 노드로 재귀호출 : 문자열의 다음위치(key+1)
			children[next]->insert(key + 1);
		}
	}

	//이 노드를 루트로 하는 트라이에서
	//문자열 key와 대응되는 노드를 찾아서 반환한다. (없으면 NULL 반환)
	TrieNode* find(const char* key) {
		if (*key == 0) return this;
		int next = toNumber(*key);
		if (children[next] == NULL) return NULL;
		return children[next]->find(key + 1);
	}
};


//트라이가 주어질 때 각 노드에 대해 failure link와 출력 문자열 목록을 계산한다.
void computeFailFunc(TrieNode* root) {
	//failure link는 root에서 BFS로 계산한다. (상위 노드의 failure func을 알아야 하므로)
	queue<TrieNode*> q;
	//루트의 failure link = 루트
	root->fail = root;
	q.push(root);
	while (!q.empty()) {
		TrieNode* here = q.front();
		q.pop();
		//here의 모든 자손의 failure를 계산하고 queue에 넣는다.
		for (int edge = 0; edge < ALPHABETS; edge++) {
			TrieNode* child = here->children[edge];
			if (!child) continue;
			//루트 다음 노드의 failure link는 root
			if (here == root) child->fail = root;
			else {
				//아닌 경우 부모의 failure link를 따라가면서 failure link를 찾는다.
				TrieNode* temp = here->fail;
				//failure link를 따라간 노드의 children 중 
				//edge번째의 failure link가 유효할 때까지 상위 노드를 타고 간다.
				while (temp != root && temp->children[edge] == NULL) 
					temp = temp->fail;
				//edge번째의 failure link가 유효하면(=not root) edge번째로 link를 만들어준다
				if (temp->children[edge]) temp = temp->children[edge];
				child->fail = temp; //root이거나 root가 아닌 failure link
			}
			//출력 문자열 목록: 실패 연결을 따라간 노드에서 복사해온 뒤,
			//이 위치에서 끝나는 문자열이 있으면 추가한다.
			child->output = child->fail->output;
			if (child->terminal != -1)
				child->output.push_back(child->terminal);
			q.push(child);
		}
	}
}

//trie에 포함된 Pattern들을 Text(=s)에서 찾는다.
//s 내에서 패턴이 출현할 때마다 (마지막 글자, 패턴 번호)의 쌍을 저장한다.
vector<pair<int, int>> ahoCorasick(const string& s, TrieNode* root) {
	vector<pair<int, int>> ret;
	TrieNode* state = root;
	//실제 반복문 내는 KMP와 다를 것 없음
	for (int i = 0; i < s.size(); i++) {
		int chr = toNumber(s[i]);
		while (state != root && state->children[chr] == NULL)
			state = state->fail;
		if (state->children[chr]) state = state->children[chr]; //유효한 faulire link를 타고 따라간다
		for (int j = 0; j < state->output.size(); j++)
			ret.push_back(make_pair(i, state->output[j])); //마지막 글자(i), 패턴 번호(output[j]) 쌍을 저장
	}
	return ret;
}

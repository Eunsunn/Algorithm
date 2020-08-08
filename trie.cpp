#include <iostream>
#include <cstring>
using namespace std;

// 알파벳 대문자만 저장하는 경우
// 각 노드는 26개의 자손을 가질 수 있다 (fixed max length)
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; } //alphabet to number
// Trie의 노드 객체
struct TrieNode {
	TrieNode* children[ALPHABETS];
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


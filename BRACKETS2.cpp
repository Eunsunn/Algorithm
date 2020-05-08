#include <iostream>
#include <stack>
using namespace std;

bool isPair();
bool isMatch(char, char);

int C;

int main() {
	cin >> C;
	
	for (int c = 0; c < C; c++){
		bool ret = isPair();
		if (ret)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}

bool isPair() {
	stack<char> st;
	string input;
	cin >> input;
	for (int i = 0; i < input.size(); i++) {
		int temp = input[i];
		if (temp == '(' || temp == '[' || temp == '{') //열림:push
			st.push(temp);
		else//닫힘
		{	
			if (st.size() == 0) return false;
			char top = st.top();
			if (isMatch(temp, top)) //괄호가 잘 닫힘
				st.pop();
			else //괄호가 제대로 안닫힘
				return false;
		}
	}
	if (!st.empty())
		return false;
	return true;
}

bool isMatch(char input, char top) {
	if (top == '(' && input == ')')
		return true;
	else if (top == '[' && input == ']')
		return true;
	else if (top == '{' && input == '}')
		return true;
	return false;
}

bool wellMatched(const string& formula) {
	//여는 괄호 문자와 닫는 괄호 문자
	const string opening("({["), closing(")}]");
	//열린 괄호를 담는 스택
	stack<char> openStack;
	for (int i = 0; i < formula.size(); i++) {
		//여는 괄호는 무조건 push
		if (opening.find[formula[i]] != -1)
			openStack.push(formula[i]);
		else { //닫는 괄호
			if (openStack.empty()) return false; //뺄 여는 괄호가 없는 경우
			if (opening.find(openStack.top()) != closing.find(formula[i])) //괄호 짝이 안맞는 경우
				return false;
			openStack.pop(); //짝이 맞으면 여는괄호를 pop
		}
	}
	return openStack.empty();
}

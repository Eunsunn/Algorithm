#include <iostream>
#include <string>
using namespace std;

string reverse(string::iterator& it) {
	char head = *it++;
	if (head == 'b' || head == 'w')
		return string(1, head);
	string upperLeft = reverse(it);
	string upperRight = reverse(it);
	string lowerLeft = reverse(it);
	string lowerRight = reverse(it);
	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

int main() {
	int cases;
	string output;

	cin >> cases;
	for (int i = 0; i < cases; i++) {
		string line;
		cin >> line;
		string::iterator it = line.begin();
		while (it != line.end())
			output = reverse(it);
		cout << output << endl;
	}
}

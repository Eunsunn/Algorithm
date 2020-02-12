//#include <iostream>
//#include <string>
//using namespace std;
//
//string reverse(string::iterator& it) {
//	char head = *it++;
//	if (head == 'b' || head == 'w')
//		return string(1, head);
//	string upperLeft = reverse(it);
//	string upperRight = reverse(it);
//	string lowerLeft = reverse(it);
//	string lowerRight = reverse(it);
//	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
//}
//
//int main() {
//	int cases;
//	string output;
//
//	cin >> cases;
//	for (int i = 0; i < cases; i++) {
//		string line;
//		cin >> line;
//		string::iterator it = line.begin();
//		while (it != line.end())
//			output = reverse(it);
//		cout << output << endl;
//	}
//}
//
////const int MAX_SIZE = pow(2, 20);
////int cases;
////char** map;
////string output;
//
////void decompress(string::iterator& it, int row, int col, int size) {
////	char tmp = *it++;
////	if (tmp == 'x') {
////		int half = size / 2;
////		decompress(it, row, col, half);
////		decompress(it, row, col + half, half);
////		decompress(it, row + half, col, half);
////		decompress(it, row + half, col + half, half);
////	}
////	else {
////		for (int i = row; i < row + size; i++)
////			for (int j = col; j < col + size; j++)
////				map[i][j] = tmp;
////	}
////}
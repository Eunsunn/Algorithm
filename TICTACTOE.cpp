#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//게임판이 주어질 때, [0, 19682] 범위의 정수로 변환
//각 칸이 3비트/ 'o'=1, 'x'=2
//한 row마다 인접하게 벡터에 저장됨
int bijection(const vector<string>& board) {
	int ret = 0;
	for(int y=0; y<3; y++)
		for (int x = 0; x < 3; x++) 
		{
			ret = ret * 3;
			if (board[y][x] == 'o') ++ret;
			else if (board[y][x] == 'x') ret += 2;
		}
	return ret;
}

//turn이 한 줄을 만들었는지 반환
bool isFinished(const vector<string>& board, char turn) {
	//열 check
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++)
		{
			if (board[y][x] != turn)
				break;
			if (y == 2)
				return true;
		}
	}
	//행 check
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++)
		{
			if (board[y][x] != turn)
				break;
			if (x == 2)
				return true;
		}
	}
	//대각선 check
	for (int i = 0; i < 3; i++)
	{
		if (board[i][i] != turn)
			break;
		if (i == 2)
			return true;
	}
	for (int i = 0; i < 3; i++)
	{
		if (board[i][2 - i] != turn)
			break;
		if (i == 2)
			return true;
	}
	return false;
}

//map의 경우의 수, -2로 초기화
int cache[19683]; 
//내가 이기면1, 비기면 0, 지면 -1 return
int canWin(vector<string>& board, char turn) {
	//기저사례: 마지막에 상대가 둬서 한 줄이 만들어진 경우
	if (isFinished(board, 'o' + 'x' - turn)) return -1;
	int& ret = cache[bijection(board)];
	if (ret != -2) return ret;
	//모든 경우의 수의 min 찾기
	int minValue = 2;
	for(int y=0; y<3; y++)
		for(int x=0; x<3; x++)
			if (board[y][x] =='.') {
				board[y][x] = turn;
				minValue = min(minValue, canWin(board, 'o' + 'x' - turn));
				board[y][x] = '.';
			}
	//플레이할 수 없거나, 비기는 경우
	if (minValue == 2 || minValue == 0) return ret = 0;
	//한쪽이 이기는 경우: 상대의 결과에 반대
	return ret = -minValue;
}

int main() {
	int test;
	cin >> test;
	for (int c = 0; c < test; c++) {
		for (int i = 0; i < 19683; i++)
			cache[i] = -2;
		int count = 0;
		vector<string> map;
		for (int i = 0; i < 3; i++) {
			string temp;
			cin >> temp;
			map.push_back(temp);
			for (int j = 0; j < 3; j++)
				if (temp[j] != '.') count++;
		}
		char turn = (count % 2 == 0 ? 'x' : 'o');
		int result = canWin(map, turn);
		if (result == 1)
			cout << turn << endl;
		else if (result == -1)
			cout << char('x'+'o'-turn) << endl;
		else if(result==0)
			cout << "TIE" << endl;
	}
}

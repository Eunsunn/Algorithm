#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//블록의 회전된 형태를 저장
vector < vector<pair<int, int>>> rotations;
//블록 크기
int blockSize;
vector<string> block;
//게임판 정보
int boardH, boardW;
vector<string> board;

//게임판의 각 칸이 덮였는지 나타내는 배열
//1이면 검은칸 또는 블럭으로 덮은 칸, 0이면 빈 칸
int cover[10][10];
//지금까지 최적해
int best;

//2차원 배열 arr을 시계방향 90도 돌린 결과 반환
vector<string> rotate(const vector<string>& arr) {
	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	for (int i = 0; i < arr.size(); i++)
		for (int j = 0; j < arr[0].size(); j++)
			ret[j][arr.size() - i - 1] = arr[i][j];
	return ret;
}
//block의 네가지 회전형태를 만들고 상대 좌표의 목록 반환
void generateRotations(vector<string> block) {
	rotations.clear();
	rotations.resize(4);
	for (int rot = 0; rot < 4; rot++) {
		int originX = -1, originY = -1;
		for (int i = 0; i < block.size(); i++)
			for (int j = 0; j < block[i].size(); j++)
				if (block[i][j] == '#') {
					if (originY == -1) {
						//가장 왼쪽 위에 있는 블록이 원점이 된다
						originY = i;
						originX = j;
					}
					//각 칸의 위치를 원점으로부터 상대좌표로 표현
					rotations[rot].push_back(make_pair(i - originY, j - originX));
				}
		//블록을 시계방향 90도 회전
		block = rotate(block);
	}
	//네가지 회전 형태 중 중복 제거
	sort(rotations.begin(), rotations.end());
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
	//블록이 몇칸짜리인지 저장
	blockSize = rotations[0].size();
}

//(y,x)부터 delta=1이면 블록을 놓고, -1이면 블럭 제거
//블록을 놓을 수 없으면 false, 가능하면 true 반환
bool set(int y, int x, const vector<pair<int, int>>& block, int delta) {
	//블록 삭제
	if (delta == -1) {
		for (int i = 0; i < block.size(); i++) {
			int tempY = y + block[i].first;
			int tempX = x + block[i].second;
			if (tempY < 0 || tempY >= boardH || tempX < 0 || tempX >= boardW)
				continue;
			cover[tempY][tempX] -= 1;
		}
		return true;
	}
	//블록 놓기
	bool out = true;
	for (int i = 0; i < block.size(); i++)
	{
		int tempY = y + block[i].first;
		int tempX = x + block[i].second;
		if (tempY < 0 || tempY >= boardH || tempX < 0 || tempX >= boardW)
		{
			out = false;
			continue;
		}
		else
		{
			if (cover[tempY][tempX] != 0)
				out = false;
			cover[tempY][tempX] += 1;
		}
	}
	return out;
}

//과대평가 휴리스틱: (빈칸 개수/블록 크기)
int maxBlock() {
	int whites = 0;
	for (int i = 0; i < boardH; i++)
		for (int j = 0; j < boardW; j++)
			if (cover[i][j] == 0)
				whites++;
	return (whites / blockSize);
}

//placed: 지금까지 놓은 블록의 수
void search(int placed) {
	//가지치기
	if (placed + maxBlock() <= best) return;
	//아직 채우지 못한 빈칸 중 가장 왼쪽 위에 있는 칸
	int y = -1, x = -1;
	for (int i = 0; i < boardH; i++) {
		for(int j=0; j<boardW; j++)
			if (cover[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		if (y != -1) break;
	}
	//기저사례: 게임판의 모든 칸을 처리한 경우
	if (y == -1) {
		best = max(best, placed);
		return;
	}
	//(x,y)를 덮는다
	for (int i = 0; i < rotations.size(); i++) {
		if (set(y, x, rotations[i], 1))
			search(placed + 1);
		set(y, x, rotations[i], -1);
	}
	//(x,y)를 덮지 않고 막아둔다
	cover[y][x] = 1;
	search(placed);
	cover[y][x] = 0;
}

int solve() {
	best = 0;
	//cover 배열 초기화
	for (int i = 0; i < boardH; i++) {
		for (int j = 0; j < boardW; j++) {
			cover[i][j] = (board[i][j] == '#' ? 1 : 0);
		}
	}
	search(0);
	return best;
}

int main() {
	int C;
	cin >> C;
	
	for (int c = 0; c < C; c++) {
		int blockH, blockW;
		cin >> boardH >> boardW >> blockH >> blockW;
		board.clear();
		block.clear();
		string line;
		for (int i = 0; i < boardH; i++)
		{
			cin >> line;
			board.push_back(line);
		}
		for (int i = 0; i < blockH; i++)
		{
			cin >> line;
			block.push_back(line);
		}
		
		//블록의 회전형태를 미리 만들어놓기
		generateRotations(block);
		//최대 블록 개수 탐색
		cout << solve() << endl;
	}
}

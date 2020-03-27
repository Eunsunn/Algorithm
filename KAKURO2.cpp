#include <iostream>
#include <cstring>
using namespace std;

//게임판 정보
//color: 각 칸의 색깔(0:검은색 or 힌트, 1:흰색)
//value: 흰 칸에 쓴 숫자(아직 안쓰면 0)
//hint: 각 칸에 해당하는 두 힌트의 번호(몇번째 힌트인지)
const int MAXN = 20, WHITE = 1;
int n, color[MAXN][MAXN], value[MAXN][MAXN], hint[MAXN][MAXN][2];
//각 힌트의 정보
//sum: 힌트 칸에 쓰인 숫자
//length: 힌트 칸에 해당하는 흰 칸의 수
//known: 힌트 칸에 해당하는 힌칸에 쓰인 숫자의 집합
int q, sum[MAXN * MAXN], length[MAXN * MAXN], known[MAXN * MAXN];

//mask에 속한 원소들의 개수를 반환
int getSize(int mask) {
	int count = 0;
	for (int i = 1; i <= 9; i++)
		if (mask & (1 << i))
			count++;
	return count;
}
//mask에 속한 원소들의 합을 반환
int getSum(int mask) {
	int sum = 0;
	for (int i = 1; i <= 9; i++)
		if (mask & (1 << i))
			sum += i;
	return sum;
}

/*
//len칸의 합이 sum이고, 이 칸들에 이미 쓰인 집합이 known일 때
//나머지 칸에 들어갈 수 있는 숫자의 집합을 반환(후보 숫자의 집합을 반환)
int getCandidates(int len, int sum, int known) {
	//조건에 부합하는 집합들의 교집합
	int allSets = 0;
	//1~9의 모든 부분집합(=모든 짝수)을 모두 생성하고, 그 중
	for (int set = 0; set < 1024; set += 2)
		//known을 포함하고, 크기가 len이며, 합이 sum인 집합 모두 찾기
		if ((set & known) == known && getSize(set) == len && getSum(set) == sum)
			allSets |= set;
	//known에 이미 속한 숫자들은 답에서 제외
	return allSets & ~known;
}
*/

//candidates[len][sum][known] = getCandidates(len, sum, known)
int candidates[10][46][1024];
//candidates[][]를 미리 계산한다
void generateCandidates() {
	//0으로 초기화
	memset(candidates, 0, sizeof(candidates));
	//1~9의 부분집합 모두 생성
	for (int set = 0; set < 1024; set += 2) {
		//집합의 크기와 원소의 합 계산
		int l = getSize(set), s = getSum(set);
		//set의 모든 부분집합에 대해 candidates[][][]를 갱신
		int subset = set;
		while (true) {
			//숫자 하나의 합이 s이고, 이미 subset 숫자가 쓰여있을 때
			//전체 숫자의 집합이 set이 되도록 나머지 숫자를 채워넣을 수 있다
			candidates[l][s][subset] |= (set & ~subset); //set-subset
			if (subset == 0) break;
			subset = (subset - 1) & set; //subset 갱신
		}
	}
}


//(y,x)에 val을 쓴다
void put(int y, int x, int val) {
	for (int h = 0; h < 2; h++)
		known[hint[y][x][h]] += (1 << val); //hint[y][x][h]의 일부로 val을 사용
	value[y][x] = val;
}
//(y,x)에 val을 지운다
void remove(int y, int x, int val) {
	for (int h = 0; h < 2; h++)
		known[hint[y][x][h]] -= (1 << val);
	value[y][x] = 0;
}
//힌트 번호(idx)가 주어질 때 후보의 집합을 반환
int getCandHint(int hint) {
	return candidates[length[hint]][sum[hint]][known[hint]];
}
//좌표가 주어질 때 해당 칸에 들어갈 수 있는 후보의 집합을 반환
//(가로, 세로 합을 모두 만족하는 후보 집합)
int getCandCoord(int y, int x) {
	return getCandHint(hint[y][x][0]) & getCandHint(hint[y][x][1]);
}
//value[]에 적힌 값(정답) 출력
void printSolution() {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << value[i][j] << " ";
		cout << endl;
	}
}

//답을 찾으면 true, 아니면 false를 반환
bool search() {
	//아직 숫자를 쓰지 않은 흰 칸중 후보의 수가 최소인 칸 찾기
	int y = -1, x = -1, minCands = 1023;
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			if (color[i][j] == WHITE && value[i][j] == 0) { //채우지 않은 흰색(빈칸)일 경우
				int cands = getCandCoord(i, j);
				if (getSize(minCands) > getSize(cands)) {
					minCands = cands;
					y = i; x = j;
				}
			}
	//해당 칸에 들어갈 숫자가 없으면 실패
	//(가로, 세로합을 모두 만족할 집합이 없는 경우)
	if (minCands == 0) return false;
	//모든 칸이 채워졌으면 출력하고 종료
	if (y == -1) {
		printSolution();
		return true;
	}
	//숫자를 하나씩 채운다
	for(int val=1; val<=9; val++)
		if (minCands & (1 << val)) {
			put(y, x, val);
			if (search()) return true;
			remove(y, x, val); //val로 채울때 오답인 경우 지워준다
		}
	return false;
}

int main() {
	int C;
	cin >> C;
	generateCandidates();
	for (int c = 0; c < C; c++) {
		memset(color, 0, sizeof(color));
		memset(value, 0, sizeof(value));
		memset(hint, 0, sizeof(hint));
		memset(sum, 0, sizeof(sum));
		memset(length, 0, sizeof(length));
		memset(known, 0, sizeof(known));
		//맵 입력
		cin >> n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> color[i][j];
		//힌트 입력
		int y, x, dir, hSum;
		cin >> q;
		for (int i = 0; i < q; i++) {
			cin >> y >> x >> dir >> hSum;
			hint[y-1][x-1][dir] = i; //좌표에 힌트 번호 표시
			sum[hint[y-1][x-1][dir]] = hSum; //힌트에 쓰인 숫자

			int ydir, xdir;
			if (dir) {//세로 힌트
				ydir = 1;
				xdir = 0;
			}
			else {//가로 힌트
				ydir = 0;
				xdir = 1;
			}
			int len = 0; //힌트의 흰 칸의 길이
			int tempY = y + ydir-1, tempX = x + xdir-1;
			//흰 칸의 힌트(가로, 세로)
			while (true) {
				if (!color[tempY][tempX]) //빈칸이 아닌 경우
					break;
				hint[tempY][tempX][dir] = i;
				len++;
				tempY += ydir;
				tempX += xdir;
			}
			length[hint[y - 1][x - 1][dir]] = len; //힌트의 길이
		}
		search();
	}
}


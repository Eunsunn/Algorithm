#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int C, n, capacity;
int volume[100], need[100];
int cache[1001][100]; //capacity, item
string name[100];

//남은 용량이 capacity일때, item번째 이후 물건들을
//담아 얻을 수 있는 최대 절박도 합
int pack(int capacity, int item) {
	//기저사례: 더 담을 물건 없을 때
	if (item == n) return 0;
	int& ret = cache[capacity][item];
	if (ret != -1) return ret;
	//item번째 물건을 담지 않는 경우
	ret = pack(capacity, item + 1);
	if(capacity>=volume[item])
		ret = max(ret, pack(capacity - volume[item], item + 1) + need[item]);
	return ret;
}

//pack(capacity, item)이 선택한 물건을 picked에 저장
void reconstruct(int capacity, int item, vector<string>& picked) {
	//기저사례: 더 담을 물건이 없을 때
	if (item == n) return;
	if (pack(capacity, item) == pack(capacity, item + 1)) //물건을 추가하지 않은 경우
		reconstruct(capacity, item + 1, picked);
	else //item번째 물건을 추가한 경우
	{
		picked.push_back(name[item]);
		reconstruct(capacity - volume[item], item + 1, picked);
	}
}

int main() {
	cin >> C;
	for (int c = 0; c < C; c++) {
		cin >> n >> capacity;
		for (int i = 0; i < n; i++)
			cin >> name[i] >> volume[i] >> need[i];
		
		memset(cache, -1, sizeof(cache));
		vector<string> picked;
		int ret = 0;
		for (int i = 0; i < n; i++) {
			int temp = pack(capacity, i);
			if (temp > ret) {
				ret = temp;
				picked.clear();
				reconstruct(capacity, i, picked);
			}
		}
		cout << ret << " " << picked.size() << endl;
		for (int i = 0; i < picked.size(); i++)
			cout << picked.at(i) << endl;
	}
}

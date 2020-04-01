// 문제: https://programmers.co.kr/learn/courses/30/lessons/42896
// 프로그래머스 카드 게임
#include <vector>
#include <algorithm>
#include <cstring> //memset

using namespace std;
const int MAX_N = 2000;
int cache[MAX_N][MAX_N]; //cache[i][j]: l[i] r[j]부터의 max점수
vector<int> l, r; //왼쪽 카드, 오른쪽 카드

//l[left], r[right]에서 시작한 max점수를 return
int search(int left, int right) {
    if (left >= l.size() || right >= r.size()) return 0;
    int& out = cache[left][right];
    if (out != -1) return out;
    out = 0;
    //왼쪽>오른쪽: 오른쪽을 버리고 점수를 얻는다
    if (l[left] > r[right])
        out = search(left, right + 1) + r[right];
    out = max(out, search(left + 1, right)); //왼쪽만 버리기
    out = max(out, search(left + 1, right + 1)); //왼쪽+오른쪽 버리기
    return out;
}

int solution(vector<int> left, vector<int> right) {
    memset(cache, -1, sizeof(cache));
    l.clear(); r.clear();
    l.assign(left.begin(), left.end()); r.assign(right.begin(), right.end());

    int answer = search(0, 0);
    return answer;
}

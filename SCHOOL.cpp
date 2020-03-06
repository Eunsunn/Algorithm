//문제: https://programmers.co.kr/learn/courses/30/lessons/42898
//프로그래머스 등굣길
#include <string>
#include <vector>

using namespace std;

const int MAX = 1000000007;
int solution(int m, int n, vector<vector<int>> puddles) {
    int map[100][100] = { 0, };
    for (int i = 0; i < puddles.size(); i++)
        map[puddles.at(i).at(1)-1][puddles.at(i).at(0)-1] = -1;
    map[0][0] = 1;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (map[r][c] < 0) continue;
            if (c - 1 >= 0 && map[r][c - 1] >= 0)
                map[r][c] = (map[r][c]+map[r][c - 1])%MAX;
            if (r - 1 >= 0 && map[r - 1][c] >= 0)
                map[r][c] = (map[r][c]+map[r - 1][c])%MAX;
        }
    }
    return map[n - 1][m - 1];
}

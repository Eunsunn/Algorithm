// 문제: 프로그래머스 단어변환
// https://programmers.co.kr/learn/courses/30/lessons/43163
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 50;
vector<string> w;
bool adj[MAXN][MAXN]; //단어끼리 연결여부

bool isAdj(string a, string b) {
    int diff = 0;
    for (int i = 0; i < a.size(); i++) {
        if (diff > 1) return false;
        if (a[i] != b[i]) diff++;
    }
    if (diff == 1) return true;
    return false;
}


//단어끼리 link 구축하기
void makeLink() {
    //단어끼리 link 구축하기
    for (int i = 0; i < w.size() - 1; i++) {
        for (int j = i + 1; j < w.size(); j++) {
            if (isAdj(w[i], w[j])) { //인접하다면
                adj[i][j] = adj[j][i] = true;
            }
        }
    }
}


int BFS(const string& begin, const string& target) {
    queue<int> q;  //BFS를 할 단어들의 인덱스를 저장한다.
    bool visit[MAXN]; //단어들의 방문 여부
    int time[MAXN]; //단어들을 방문한 시각
    memset(visit, 0, sizeof(visit));
    memset(time, 0, sizeof(time));

    //begin 단어와 인접한 단어들을 queue에 넣고 BFS 시작한다.
    for(int i=0; i<w.size(); i++)
        if (isAdj(begin, w[i])) {
            q.push(i);
            visit[i] = true;
            time[i] = 1;
        }

    //begin->target으로 가는 BFS 수행(begin!=target이다)
    while (!q.empty()) {
        int idx = q.front(); q.pop();
        //목적지에 도달하면 종료한다
        if (w[idx] == target) return time[idx];
        //그렇지 않으면 다른 인접한 단어들을 방문한다.
        for (int i = 0; i < w.size(); i++){
            bool connect = adj[idx][i];
            if (connect && !visit[i]) //연결 & not 방문이어야 방문
            {
                q.push(i);
                visit[i] = true;
                time[i] = time[idx] + 1;
            }
        }

    }

    return 0;
}

int solution(string begin, string target, vector<string> words) {
    w = words;
    //단어끼리 링크 만들기
    memset(adj, 0, sizeof(adj));
    makeLink();

    //BFS로 최단거리 찾기
    int answer = BFS(begin, target);
    return answer;
}

//int main() {
//    vector<string> words = { "hot", "dot", "dog", "lot", "log", "cog" };
//    string begin = "hit";
//    string target = "cog";
//
//    cout << solution(begin, target, words) << endl;
//}


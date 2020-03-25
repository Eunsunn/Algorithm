#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <intrin.h>
using namespace std;

//TSP: Traveling Salesman Problem

/*완전탐색*/
const double INF = 1e200;
const int MAX = 30; //최대 도시 수
int n; //도시 수
double dist[MAX][MAX]; //두 도시간 거리 저장
//지금까지 찾은 최적해
double best;
////path: 지금까지 이동한 경로, visited:도시방문여부, currentLength:지금까지 만든 도시의 길이
//void search(vector<int>& path, vector<bool>& visited, double currentLength) {
//	int here = path.back();
//	//기저사례; 모두 방문했을 때는 시작도시(0번)으로 돌아간다
//	if(path.size()==n){
//		best = min(best, currentLength + dist[here][0]);
//		return;
//	}
//	//다음 방문할 도시를 전부 시도
//	for (int next = 0; next < n; next++)
//	{
//		if (visited[next]) continue;
//		path.push_back(next);
//		visited[next] = true;
//		//나머지 경로: 재귀호출
//		search(path, visited, currentLength + dist[here][next]);
//		visited[next] = false;
//		path.pop_back();
//	}
//}
//double solve() {
//	best = INF;
//	vector<bool> visited(n, false);
//	vector<int> path(1, 0);
//	visited[0] = true;
//	search(path, visited, 0);
//	return best;
//}


/* simple heuristic */
//각 도시에 인접한 edge중 가장 짧은 것을 미리 구해논다.
double minEdge[MAX];
//단순한 형태의 휴리스틱
double simpleHeuristic(vector<bool>& visited) {
	double ret = minEdge[0];
	//현재 경로에서 방문하지 않은 도시를 모두 방문하는 경로 짐작
	for (int i = 0; i < n; i++)
		if (!visited[i])
			ret += minEdge[i];
	return ret;
}
//void search(vector<int>& path, vector<bool>& visited, double currentLength) {
//	//단순 휴리스틱을 이용해 pruning
//	if (best <= currentLength + simpleHeuristic(visited)) return;
//
//	int here = path.back();
//	//기저사례; 모두 방문했을 때는 시작도시(0번)으로 돌아간다
//	if (path.size() == n) {
//		best = min(best, currentLength + dist[here][0]);
//		return;
//	}
//	//다음 방문할 도시를 전부 시도
//	for (int next = 0; next < n; next++)
//	{
//		if (visited[next]) continue;
//		path.push_back(next);
//		visited[next] = true;
//		//나머지 경로: 재귀호출
//		search(path, visited, currentLength + dist[here][next]);
//		visited[next] = false;
//		path.pop_back();
//	}
//}
//double solve() {
//	//simpleHeuristic을 위한 초기화
//	for (int i = 0; i < n; i++) {
//		minEdge[i] = INF;
//		for (int j = 0; j < n; j++)
//			if (i != j) minEdge[i] = min(minEdge[i], dist[i][j]);
//	}
//	//탐색
//	best = INF;
//	vector<bool> visited(n, false);
//	vector<int> path(1, 0);
//	visited[0] = true;
//	search(path, visited, 0);
//	return best;
//}


///* 가까운 도시부터 방문하기(탐욕법) */
////각 도시마다 다른 도시들을 가까운 순서대로 정렬
//vector<int> nearest[MAX];
//void search(vector<int>& path, vector<bool>& visited, double currentLength) {
//	int here = path.back();
//	//기저사례; 모두 방문했을 때는 시작도시(0번)으로 돌아간다
//	if (path.size() == n) {
//		best = min(best, currentLength + dist[here][0]);
//		return;
//	}
//	//다음 방문할 도시를 전부 시도: 거리가 가까운 순서
//	for (int i = 0; i < nearest[i].size(); i++) {
//		int next = nearest[here][i];
//		if (visited[next]) continue;
//		path.push_back(next);
//		visited[next] = true;
//		//나머지 경로: 재귀호출
//		search(path, visited, currentLength + dist[here][next]);
//		visited[next] = false;
//		path.pop_back();
//	}
//}
//double solve() {
//	//nearest 초기화
//	for (int i = 0; i < n; i++) { //i번째 도시와 가까운 순서로 도시를 정렬
//		vector<pair<double, int>> order; //pair: (거리, 도시)
//		for (int j = 0; j < n; j++)
//			if (i != j)
//				order.push_back(make_pair(dist[i][j], j));
//		sort(order.begin(), order.end());
//		nearest[i].clear();
//		for (int j = 0; j < n - 1; j++)
//			nearest[i].push_back(order[j].second);
//	}
//	//탐색
//	best = INF;
//	vector<bool> visited(n, false);
//	vector<int> path(1, 0);
//	visited[0] = true;
//	search(path, visited, 0);
//	return best;
//}


///* 지나온 경로로 가지치기 */
////path의 마지막 네 도시 중 가운데 두 도시의 순서를 바꿀 때
////경로가 더 짧아지는지 여부를 반환
//// [p, a, b, q] -> [p, b, a, q]
//bool pathSwapPruning(const vector<int>& path) {
//	if (path.size() < 4) return false;
//	int p = path[path.size() - 4];
//	int a = path[path.size() - 3];
//	int b = path[path.size() - 2];
//	int q = path[path.size() - 1];
//	return dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q];
//}
////시작 도시와 현재 도시를 제외한 path의 부분 경로를
////뒤집어보고 짧아지는 지 확인(현재 교차되는 경로인지 확인)
////[... p,a, ... b,q ...] -> [... p,b, ... a,q ...]
//bool pathReversePruning(const vector<int>& path) {
//	if (path.size() < 4) return false;
//	int b = path[path.size() - 2];
//	int q = path[path.size() - 1];
//	for (int i = 0; i + 3 < path.size(); i++)
//	{
//		int p = path[i];
//		int a = path[i + 1];
//		if (dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q])
//			return true; //교차됨
//	}
//	return false;
//}


///* 최소비용트리(MST)를 이용한 Pruning */
////상호 배타적 집합 자료구조 구현
//struct DisjointSet {
//	//n개의 원소로 구성된 집합 자료구조
//	DisjointSet(int n);
//	//here가 포함된 집합의 대표 반환
//	int find(int here);
//	//a가 포함된 집합과 b가 포함된 집합을 합침
//	bool merge(int a, int b);
//};
////모든 도시 간의 edge를 길이 순으로 정렬
//vector<pair<double, pair<int, int>>> edges;
////here와 시작점, 아직 방문하지 않은 도시를 모두 연결하는 MST
//double mstHeuristic(int here, const vector<bool>& visited) {
//	//크루스칼 MST
//	DisjointSet sets(n);
//	double taken = 0;
//	for (int i = 0; i < edges.size(); i++) {
//		int a = edges[i].second.first, b = edges[i].second.second;
//		if (a != 0 && a != here && visited[a]) continue;
//		if (b != 0 && b != here && visited[b]) continue;
//		if (sets.merge(a, b))
//			taken += edges[i].first;
//	}
//	return taken;
//}
//double solve() {
//	//edges 초기화
//	edges.clear();
//	for (int i = 0; i < n; i++)
//		for (int j = 0; j < n; j++)
//			edges.push_back(make_pair(dist[i][j], make_pair(i, j)));
//	sort(edges.begin(), edges.end());
//	//nearest 초기화
//	for (int i = 0; i < n; i++) { //i번째 도시와 가까운 순서로 도시를 정렬
//		vector<pair<double, int>> order; //pair: (거리, 도시)
//		for (int j = 0; j < n; j++)
//			if (i != j)
//				order.push_back(make_pair(dist[i][j], j));
//		sort(order.begin(), order.end());
//		nearest[i].clear();
//		for (int j = 0; j < n - 1; j++)
//			nearest[i].push_back(order[j].second);
//	}
//	//탐색
//	best = INF;
//	vector<bool> visited(n, false);
//	vector<int> path(1, 0);
//	visited[0] = true;
//	search(path, visited, 0);
//	return best;
//}


/* 메모이제이션 */
//남은 도시의 수가 CACHED_DEPTH 이하이면 DP로 바꿈
const int CACHED_DEPTH = 5;
//cache[here][남은도시 수][도시 visited(정수)] = 경로의 길이
map<int, double> cache[MAX][CACHED_DEPTH + 1];
//나머지 도시를 모두 방문하고 시작점으로 돌아가는 최단 경로의 길이
double dp(int here, int visited) {
	//기저사례: 더 방문할 도시가 없음 -> 시작점으로 돌아감
	if (visited = (1 << n) - 1) return dist[here][0];
	//메모이제이션
	int remaining = n - __popcnt(visited);
	double& ret = cache[here][remaining][visited];
	if (ret > 0) return ret;
	ret = INF;
	//다음 도시 모두 시도
	for (int next = 0; next < n; next++) {
		if (visited & (1 << next)) continue;
		ret = min(ret, dp(next, visited + (1 << next)) + dist[here][next]);
	}
	return ret;
}
void search(vector<int>& path, int visited, double currentLength) {
	int here = path.back();
	//기저사례; 모두 방문했을 때는 시작도시(0번)으로 돌아간다
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	//기저사례: 남은 도시의 수가 CACHED_DEPTH이하면 DP로 바꿈
	if (path.size() + CACHED_DEPTH >= n) {
		best = min(best, currentLength + dp(path.back(), visited));
		return;
	}
	//모든 경우 탐색(생략)
}


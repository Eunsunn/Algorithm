#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//네트워크의 유량을 계산하는 포드-풀커슨 알고리즘
const int INF = 987654321;
const int MAX_V = 100;
int V;
//capacity[u][v] = u에서 v로 흘려보낼 수 있는 용량
//flow[u][v] = 현재 u에서 v로 흘러가는 유량 (반대 방향은 음수)
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

//source에서 sink로 가는 flow를 계산하고 총 유량을 반환한다.
int networkFlow(int source, int sink) {
	//flow는 처음에 0으로 초기화
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	while (true) {
		//BFS로 증가 경로를 찾음
		vector<int> parent(MAX_V, -1); //유량에서 지나온 경로를 표시한다 (i번째 vertex의 부모 vertex를 표시) -> DFS와 유사한 기능
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) { //parent[sink] == -1을 통해 source->sink 의 "한" 경로를 찾는다. 
			int here = q.front(); q.pop();
			for(int there = 0; there < MAX_V; there++)
				//잔여용량이 남은 노드를 방문하고 queue에 넣는다.
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
		}
		//증가 경로가 없으면 종료한다. (더이상 유량을 추가하지 못할 경우)
		if (parent[sink] == -1) break;
		//parent vertex를 따라가면서 증가 경로를 통해 유량을 얼마나 보낼 지 결정한다.
		int amount = INF;
		for (int p = sink; p != source; p = parent[p])
			amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount); //추가할 수 있는 용량은 경로의 유량의 최솟값 (용량 제한 속성)
		//증가 경로를 통해 유량 증가시킨다.
		for (int p = sink; p != source; p = parent[p])
		{
			flow[parent[p]][p] += amount; //보내는 쪽은 +유량
			flow[p][parent[p]] -= amount; //받는 쪽은 -유량
		}
		totalFlow += amount;
	}
	return totalFlow;
}



//인접 리스트로 포드-풀커슨 알고리즘 구현
//이때, 반대방향 간선에 대한 포인터를 객체에 담아 빠르게 반대 방향의 유량도 갱신하도록 한다!

//간선의 정보를 나타내는 구조체
struct Edge {
	int target, capacity, flow;
	//역방향 간선의 포인터
	Edge* reverse;
	//이 간선의 잔여 용량을 계산한다
	int residualCapacity() const { return capacity - flow; }
	//이 간선을 따라 용량 amt를 내보낸다 - 역방향 간선의 flow도 갱신
	void push(int amt) {
		flow += amt;
		reverse->flow -= amt;
	}
};
//유량 네트워크의 인접 리스트
vector<Edge*> adj[MAX_V]; //각 노드마다 인접 노드의 포인터 벡터(vector<Edge*>)를 가진다
//u에서 v로 가는 간선을 추가한다
void addEdge(int u, int v, int capacity) {
	Edge* uv = new Edge(), *vu = new Edge();
	//u에서 v로 가는 edge 초기화
	uv->target = v;
	uv->capacity = capacity;
	uv->flow = 0;
	uv->reverse = vu;
	//v에서 u로 가는 edge 초기화 (유량을 상쇄하는 데에만 사용할 유령 간선)
	vu->target = u;
	vu->capacity = 0;
	vu->flow = 0;
	vu->reverse = uv;
	adj[u].push_back(uv);
	adj[v].push_back(vu);
}

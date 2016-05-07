#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;


//adjacent[v1] = (v2, cost)는 v1는 v2와 연결되어 있는 것이고 거리는 cost다
vector < pair<int, double> > adj[10000];
std::numeric_limits<double> a;
const double INF = a.max();

double dijkstra(int src, int V){
	//먼저 거리 초기화
	vector<double> distance(V, INF);
	//printf("%lf\n", INF);
	priority_queue<pair<double, int>> pq;
	distance[src] = 1.0;
	pq.push(make_pair(-1.0, src));

	while (!pq.empty()){
		double cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		//만약 cost가 더 크다면 이미 더 작은 것으로 업데이트 됐다는 것을 의미한다
		if (distance[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); ++i){
			int there = adj[here][i].first;
			double nextDist = cost * adj[here][i].second;
			//만약 원래 경로보다 더 좋은 것을 찾았다면
			if (distance[there] > nextDist){
				distance[there] = nextDist;
				//printf("%f\n", nextDist);
				pq.push(make_pair(-nextDist, there));
			}
		}

	}
	//src과 V-1의 거리를 return
	return distance[V - 1];
}

int main(void){

	int Test_Case;
	int V, E;
	int v1, v2;
	double value;
	double result;

	//freopen("input.txt", "r", stdin);
	scanf("%d", &Test_Case);
	for (int i = 1; i <= Test_Case; ++i){
		//초기화
		for (int i = 0; i < 10000; ++i){
			adj[i].clear();
		}
	
		scanf("%d%d", &V, &E);
		for (int i = 0; i < E; ++i){
			scanf("%d%d%lf", &v1, &v2, &value);
			adj[v1].push_back(make_pair(v2, value));
			adj[v2].push_back(make_pair(v1, value));
		}

		result = dijkstra(0, V);

		printf("%0.10f\n", result);
	}

	return 0;
}

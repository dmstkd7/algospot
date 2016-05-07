#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

//pair의 first는 이어지는 정점 second는 가중치이다
vector<pair<int, int>> adj[1001];
std::numeric_limits<int> a;
const int INF = a.max();

vector<int> findMinDistance(int V, int src){
	//src가 0이라고 생각해보자
	vector<int> distance(V, INF);
	//queue에 들어가는 pair의 first는 가중치, second가 이어지는 점이다
	priority_queue<pair<int, int>> pq;
	distance[src] = 0;
	pq.push(make_pair(0, src));

	while (!pq.empty()){
		//printf("ff\n");
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (distance[here] < cost) continue;

		for (int i = 0; i < adj[here].size(); ++i){
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			if (distance[there] > nextDist){
				distance[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	

	return distance;
}


int main(void){

	int Test_Case;
	int V, E, n, m;
	int v1, v2, c;
	vector<int> distance;
	int result;
	vector<int> n_num;
	int temp;

//	freopen("input.txt", "r", stdin);
	scanf("%d", &Test_Case);
	for (int i = 1; i <= Test_Case; ++i){
		//초기화
		for (int i = 0; i < 1001; ++i)
			adj[i].clear();
		n_num.clear();
		result = 0;

		scanf("%d%d%d%d", &V, &E, &n, &m);
		for (int i = 0; i < E; ++i){
			scanf("%d%d%d", &v1, &v2, &c);
			adj[v1].push_back(make_pair(v2, c));
			adj[v2].push_back(make_pair(v1, c));
		}


		//화재 갯수
		for (int i = 0; i < n; ++i){
			scanf("%d", &temp);
			n_num.push_back(temp);
		}

		//소방차는 미리 연결해둔다
		for (int i = 0; i < m; ++i){
			scanf("%d", &temp);
			adj[0].push_back(make_pair(temp, 0));
		}

			
		//V는 정점의 갯수 0은 소방서의 위치를 나타내는 거야
		//1000 소방서에서 불난 곳까지 거리를 측정
		distance = findMinDistance(V+1, 0);
	
		for (int i = 0; i < n; ++i)
			result += distance[n_num[i]];

		printf("%d\n", result);
	}

	return 0;
}

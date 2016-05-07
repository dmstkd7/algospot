#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;


//첫 번째는 연결되는 점, 두 번째는 cost입니다
vector<pair<int, int>> adj[100];
bool reachable[100][100];
vector<bool> reach[100];
std::numeric_limits<int> a;

const int INF = a.max()-1000000;
int V, E;



void setReach(){


	for (int k = 0; k < V; ++k)
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j){
				if (!reachable[i][j] && (reachable[i][k] && reachable[k][j]))
					reachable[i][j] = true;
			}

}



int bellmanFord(int start, int finish){

	vector<int> upper(V, a.max()-100000);
	//bool updated;
	upper[start] = 0;

	//먼저 V-1번 다 돌려본다
	for (int iter = 0; iter < V - 1; ++iter){
		//	updated = false;
		for (int here = 0; here < V; ++here){
			for (int i = 0; i < adj[here].size(); ++i){
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				upper[there] = min(upper[there], upper[here] + cost);
			}

		}
		//	if (!updated) break;
	}

	//V번 해서 된다면 마이너스가 있는 것이다 
	//마이너스가 있는데 만약 이것이 0과 1사이에 있다면 x는 발산한다.
	for (int here = 0; here < V; ++here){
		for (int i = 0; i < adj[here].size(); ++i){
			int there = adj[here][i].first;
			int cost = adj[here][i].second;
			//또 완화가 되고 그 사이에 경로가 있따면 -INF를 반환해라
			if (upper[there] > upper[here] + cost)
				if (reachable[start][here] && reachable[here][finish])
					return -INF;
		}
	}


	return upper[finish];
}


int main(void){

	int Test_Case;
	int v1, v2, w;
	int max_result, min_result;

	//	freopen("input.txt", "r", stdin);
	scanf("%d", &Test_Case);
	for (int i = 1; i <= Test_Case; ++i){
		//초기화
		for (int i = 0; i < 100; ++i){
			adj[i].clear();
			reach[i].clear();
		}

		for (int i = 0; i < 100; ++i)
			for (int j = 0; j < 100; ++j)
				reachable[i][j] = false;


		scanf("%d%d", &V, &E);
		for (int i = 0; i < E; ++i){
			scanf("%d%d%d", &v1, &v2, &w);
			reachable[v1][v2] = true;
			adj[v1].push_back(make_pair(v2, w));
		}
		setReach();

		min_result = bellmanFord(0, 1);

		for (int i = 0; i < V; ++i)
			for (int j = 0; j < adj[i].size(); ++j)
				adj[i][j].second = -adj[i][j].second;


		max_result = bellmanFord(0, 1);

		if (min_result >= a.max()-1000000){
			printf("UNREACHABLE\n");
			continue;
		}

		if (min_result == -INF)
			printf("INFINITY ");
		else
			printf("%d ", min_result);

		if (max_result == -INF)
			printf("INFINITY\n");
		else
			printf("%d\n", -max_result);



	}

	return 0;
}

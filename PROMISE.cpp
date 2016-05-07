#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

//정점의 갯수
const int MAX_V = 210;
const int MAX = 1000100;

int adj[MAX_V][MAX_V];
int add_adj[MAX_V][MAX_V];
int V, E, FE;
vector <pair<int, int>> add;
int counter = 0;


void addVertex(int v1, int v2, int w){

	if (adj[v1][v2] <= w){
		counter++;
		return;
	}

	for (int i = 0; i < V; ++i)
		for (int j = 0; j < V; ++j){
			adj[i][j] = min(adj[i][j], min(adj[i][v1] + w + adj[v2][j], adj[i][v2] + w + adj[v1][j]));
		}

}

void floyd(){

	//먼저 플로이드를 해서 최단거리를 미리 구해놓는다
	for (int i = 0; i < V; ++i) adj[i][i] = 0;
	for (int k = 0; k < V; ++k)
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				if (adj[i][j] > adj[i][k] + adj[k][j]){
					adj[i][j] = adj[i][k] + adj[k][j];
				}
}


int main(void){

	int Test_Case;
	int v1, v2, w;
	int result;


//	freopen("input.txt", "r", stdin);
	scanf("%d", &Test_Case);
	for (int i = 1; i <= Test_Case; ++i){
		//초기화
		V = 0;  E = 0; FE = 0;
		counter = 0;
		add.clear();
		for (int i = 0; i < MAX_V; ++i)
			for (int j = 0; j < MAX_V; ++j){
				adj[i][j] = MAX;
			}


		scanf("%d%d%d", &V, &E, &FE);
		for (int i = 1; i <= E; ++i){
			scanf("%d%d%d", &v1, &v2, &w);
			adj[v1][v2] = w;
			adj[v2][v1] = w;
		}
		floyd();
		for (int i = 1; i <= FE; ++i){
			scanf("%d%d%d", &v1, &v2, &w);
			addVertex(v1, v2, w);
		}

	//	result = floyd();
		printf("%d\n", counter);

	}

	return 0;
}

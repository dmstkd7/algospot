#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <memory.h>
using namespace std;


int V;
int vertex[510];
int adj[510][510];
int W[510][510];
std::numeric_limits<int> a;



void floyd(){
	
	//order를 sort하는 이유는 u에서 v로 가는 길 중에 
	//사실상 작은 점은 중요하지 않다 최악의 길을 찾아야 하기 때문이다
	vector<pair<int, int>> order;
	for (int i = 0; i < V; ++i)
		order.push_back(make_pair(vertex[i], i));
	sort(order.begin(), order.end());


	for (int i = 0; i < V; ++i)
		for (int j = 0; j < V; ++j){
			if (i == j)
				W[i][j] = 0;
			else
				W[i][j] = adj[i][j];

		}

	for (int k = 0; k < V; ++k){
		int w = order[k].second;
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j){
				adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
				W[i][j] = min(W[i][j], adj[i][w] + vertex[w] + adj[w][j]);
			}
	}
		
}

void proc(){

	int v1, v2, w;
	int E;

	//초기화
	V = 0;
	E = 0;
	for (int j = 0; j < 510; ++j){
		vertex[j] = 0;
		for (int k = 0; k < 510; ++k){
			adj[j][k] = 987654321;
		}
	}

	//입력을 받는 곳
	scanf("%d%d", &V, &E);
	for (int j = 0; j < V; ++j)
		scanf("%d", &vertex[j]);

	for (int j = 0; j < E; ++j){
		scanf("%d%d%d", &v1, &v2, &w);
		adj[v1-1][v2-1] = w;
		adj[v2-1][v1-1] = w;
	}


}

int main(void){

	int Test_Case;
	int result;
	int start, finish;

//	freopen("input.txt", "r", stdin);
	proc();

	floyd();
	scanf("%d", &Test_Case);
	for (int i = 1; i <= Test_Case; ++i){
		scanf("%d%d", &start, &finish);
		printf("%d\n", W[start-1][finish-1]);
	}

	return 0;
}

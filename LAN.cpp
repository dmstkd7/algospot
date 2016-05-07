#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <math.h>
using namespace std;

std::numeric_limits<double> a;
const double INF = a.max();
const int MAX_V = 501;

vector< pair<int, double> > adj[MAX_V];

double getDistance(int V){
	vector< pair<int, int> > selected;

	vector<bool> added(V, false);
	vector<double> minWeight(V, INF);
	vector<int> parent(V, -1);
	double ret = 0;
	minWeight[0] = parent[0] = 0;
	for (int iter = 0; iter < V; ++iter){
		int u = -1;

		for (int v = 0; v < V; ++v){
			if (!added[v] && (u == -1 || minWeight[u] > minWeight[v]))
				u = v;
		}
		if (parent[u] != u)
			selected.push_back(make_pair(parent[u], u));
		ret += minWeight[u];
		added[u] = true;

		for (int i = 0; i < adj[u].size(); ++i){
			int nextV = adj[u][i].first;
			double weight = adj[u][i].second;

			if (u== adj[u][i].first) continue;
			
			if (!added[nextV] && minWeight[nextV] > weight){
				parent[nextV] = u;
				minWeight[nextV] = weight;
			}
		}
	}

	return ret;
}

double getD(int i, int j, vector< pair<int, int> >& selected){
	
	double result;
	double x, y;

	x = selected[i].first - selected[j].first;
	y = selected[i].second - selected[j].second;
	result = x*x + y*y;
//	printf("%d %d %d %d %f\n", selected[i].first, selected[i].second, selected[j].first, selected[j].second, result);
	return sqrt(result);
}

int main(void){

	int Test_Case;
	int V, E;
	int temp;
	int d1, d2, t1, t2;
	double result;
	vector< pair<int, int> > selected;


//	freopen("input.txt", "r", stdin);
	scanf("%d", &Test_Case);
	for (int i = 1; i <= Test_Case; ++i){
		for (int i = 0; i < MAX_V; ++i)
			adj[i].clear();
		selected.clear();

		scanf("%d%d", &V, &E);
		for (int i = 0; i < V; ++i){
			scanf("%d", &temp);
			selected.push_back(make_pair(temp, 0));
		}
		for (int i = 0; i < V; ++i){
			scanf("%d", &temp);
			selected[i].second = temp;
		}
		
		for (int i = 0; i < V; ++i){
			for (int j = 0; j < V; ++j)
					adj[i].push_back(make_pair(j, getD(i, j, selected)));
		}


		for (int i = 0; i < E; ++i){
			scanf("%d%d", &t1, &t2);
			adj[t1][t2].second = 0;
			adj[t2][t1].second = 0;
		}

		result = getDistance(V);

		printf("%0.10f\n", result);
	}

	return 0;
}

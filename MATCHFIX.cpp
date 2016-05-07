#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <memory.h>
using namespace std;
const int MAX_V = 210;
const int INF = 987654321;


int capacity[MAX_V][MAX_V];
int flow[MAX_V][MAX_V];
int wins[20];
int match[MAX_V][2];
int game, player;
int V;


int networkFlow(int source, int sink){
	int totalFlow = 0;
	memset(flow, 0, sizeof(flow));
	while (true){
		vector<int> parent(MAX_V, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1){
			int here = q.front();
			q.pop();
			for (int there = 0; there < V; ++there){
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1){
					q.push(there);
					parent[there] = here;
				}
			}
		}
		if (parent[sink] == -1) break;
		int amount = INF;
		for (int p = sink; p != source; p = parent[p])
			amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);

		for (int p = sink; p != source; p = parent[p]){
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}


	return totalFlow;

}

bool canWinWith(int totalWins){

	//혹시 기존에 있는 사람들 중에 totalwin을 채운 사람이 있으면 false 리턴
	if (*max_element(wins + 1, wins + player) >= totalWins)
		return false;

	//0이 source 1이 terminal 이기 때문에 2를 더해준거
	V = 2 + game + player;
	memset(capacity, 0, sizeof(capacity));
	for (int i = 0; i < game; ++i){
		capacity[0][2 + i] = 1;
		for (int j = 0; j < 2; ++j)
			capacity[2 + i][2 + game + match[i][j]] = 1;
	}
	for (int i = 0; i < player; ++i){
		int maxWin = (i == 0 ? totalWins : totalWins - 1);
		capacity[2 + game + i][1] = maxWin - wins[i];
	}

	return (networkFlow(0, 1) == game && capacity[2 + game][1] == flow[2 + game][1]);

}


int possibleWin(){
	int count = 0;
	//0번에게 갈 수 있는게 있냐
	for (int i = 0; i < game; ++i){
		if (match[i][0] == 0 || match[i][1] == 0)
			count++;
	}
	return count;
}

int main(void){
	int Test_Case;
	int wc;
	int g1, g2;
	bool result;
	int first;
	int count;

	//freopen("input.txt", "r", stdin);
	scanf("%d", &Test_Case);
	for (int i = 1; i <= Test_Case; ++i){
		//초기화
		memset(flow, 0, sizeof(flow));
		memset(capacity, 0, sizeof(capacity));
		memset(wins, 0, sizeof(wins));
		memset(match, 0, sizeof(match));
		result = false;


		scanf("%d%d", &player, &game);
		for (int i = 0; i < player; ++i){
			scanf("%d", &wc);
			wins[i] = wc;
		}

		for (int i = 0; i < game; ++i){
			scanf("%d%d", &g1, &g2);
			match[i][0] = g1;
			match[i][1] = g2;
		}
		first = wins[0];

		count = possibleWin();

		for (int i = 0; i < 200; ++i){
			if (count < first-wins[0]) break;
			result = canWinWith(first);
			if (result == true) break;
			first++;
		}
		
		if (result == false)
			printf("-1\n");
		else
			printf("%d\n", first);

	}

	return 0;
}

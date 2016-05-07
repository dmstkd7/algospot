//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;



struct DisjointSet {
	vector<int> parent, rank, enemy, size;
	DisjointSet(int n) : parent(n), rank(n, 1), enemy(n, -1), size(n,1) {
		for (int i = 0; i < n; ++i)
			parent[i] = i;
	}
	
	//루트를 찾는 함수
	int find(int u){
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}
	
	//u와 v를 합치는 함수
	int merge(int u, int v){

		//u, v중 자기자신을 가리키고 있는 것은 제외시킨다
		if (u == -1 || v == -1) return max(u, v);
		u = find(u);
		v = find(v);

		if (u == v) return u;
		if (rank[u]> rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v]) ++rank[v];
		size[v] += size[u];
		return v;

	}

	//ACK 일 경우
	//u와 v를 합치고 v의 적의 루트를 u의 적으로 돌린다
	int ACK(int u, int v){
		//1.u와 v가 적이 아닌지 먼저 확인해본다
		u = find(u);
		v = find(v);
		if (enemy[u] == v) return -1;
	
		int a = merge(u, v);
		int b = merge(enemy[u], enemy[v]);
		//적대적 관계에 있는 루트들끼리 적을 맺는다
		enemy[a] = b;

		//만약 b가 1이면 패스 하고 아니라면 적을 만든다
		if (b != -1) enemy[b] = a;

		return 0;

	}
	//DIS 일 경우
	int DIS(int u, int v){
		//적대적 관계를 만들려고 했는데 같은 편이면 오류 발생시킨다
		u = find(u);
		v = find(v);
		if (u==v) return -1;

		int a = merge(u, enemy[v]);
		int b = merge(v, enemy[u]);
		enemy[a] = b;
		enemy[b] = a;
		return 0;
	}

	int comparedSize(const DisjointSet& buf, const int& n){
		int ret = 0;
		for (int node = 0; node < n; ++node){
			if (buf.parent[node] == node){
				int enemy = buf.enemy[node];
				//만약 적이 있었다면
				if (enemy > node) continue;
				int mySize = buf.size[node];
				int enemySize = (enemy == -1 ? 0 : buf.size[enemy]);
				ret += max(mySize, enemySize);
			}
		}
		return ret;
		
	}

};

int main(void)
{
	int Test_Case;
	int N, M;
	char temp[4];		//ACK,DIS인지 임시
	int a, b;			//임시
	int check, j, ch;
	

	//freopen("input.txt", "r", stdin);

	scanf("%d", &Test_Case);
	for (int i = 1; i <= Test_Case; ++i){
		ch = 0;
		scanf("%d%d", &N, &M);
		struct DisjointSet set(N);					//set함수 만들기
		for (j = 0; j < M; ++j){
			scanf("%s", temp);
			scanf("%d%d", &a, &b);
			//만약ACK면
			if (!strcmp("ACK", temp))
				check = set.ACK(a, b);
			//만약 DIS라면
			else
				check = set.DIS(a, b);
		
			if (check == -1 && ch == 0){
				ch = -(j + 1);
			}
				
			
		}
		if (ch <0)
			printf("CONTRADICTION AT %d\n", -ch);
		else
			printf("MAX PARTY SIZE IS %d\n", set.comparedSize(set, N));
		
		

	}



	return 0;
}

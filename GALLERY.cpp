#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;

int install;
vector<int> adj[1000];
vector<bool> visited;
const int UNWATCHED = 0;
const int WATCHED = 1;
const int INSTALLED = 2;


int dfs(int here){

	visited[here] = true;
	int children[3] = { 0, 0, 0 };

	//만약 here에 자식이 있다면 자식을 조사
	for (int i = 0; i < adj[here].size(); i++){
		int there = adj[here][i];
		if (!visited[there])
			++children[dfs(there)];
	}
	
	//자식이 UNWATCHED라면 install 횟수를 증가시키고 INSTALLED 했다고 해라
	if (children[UNWATCHED]){
		++install;
		return INSTALLED;
	}
	//INSTALLED 되었다면 WATCH 라고 해라s
	if (children[INSTALLED]){
		return WATCHED;
	}

	//만약 자식들이 아에 없는 잎노드라면 UNWATCHED를 돌려준다
	return UNWATCHED;

}


int main(void)
{
	int Test_Case;
	int a, b;
	int N, M;

	//인접한 것 나타내는 것

//	freopen("input.txt", "r", stdin);

	scanf("%d", &Test_Case);
	for (int i = 1; i <= Test_Case; i++){
		//초기화
		install = 0;
		visited.clear();
		for (int i = 0; i < 1000; i++)
			adj[i].clear();


		scanf("%d%d", &N, &M);
		visited = vector<bool>(N, false);
		//연결점 설정 vector의 연결점으로 설정
		for (int i = 0; i < M; i++){
			scanf("%d%d", &a, &b);
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		
		for (int i = 0; i < N; i++){
			//아직 방문하지 않았고 그 곳이 UNWATCHED라면 설치해라
			if (!visited[i] && dfs(i) == UNWATCHED)
				++install;
		}

		printf("%d\n", install);

	}

	return 0;

}

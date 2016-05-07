#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

vector<vector<int>> adj;
vector<int> seen, order;


void makeGraph(string *words,int word_size){
	adj = vector<vector<int>>(26, vector<int>(26, 0));
	int len;
	
	for (int i = 1; i < word_size; ++i){
		int j = i - 1;
		//인접한 두 숫자만 비교한다. 예를들어 A,C면 A,B B,C를 조사한다.
		len = min(words[j].size(), words[i].size());
		for (int k = 0; k < len; ++k){
			//단어가 다른 것을 찾으면 adj의 a,b는 연결 되었다고 표시한다.
			// 0 0 0 0 0 
			// 0 0 1 0 0
			// 0 0 0 1 0 
			// 이런식으로 되는 것이다 오른쪽 위만 연결
			if (words[j][k] != words[i][k]){
				int a = words[j][k] - 'a';
				int b = words[i][k] - 'a';
				adj[a][b] = 1;
				break;
			}
		}
	}

}


void dfs(int here){
	//here에서 봤던 것은 표시해둔다, 
	seen[here] = 1;
	//
	for (int there = 0; there < adj.size(); ++there)
		//here 연결된 것 중 마지막에 붙어 있는 것을 출력한다
		if (adj[here][there] && !seen[there])
			dfs(there);
	//다 돌았다 싶으면 order에 넣는다
	order.push_back(here);
}

vector<int> topologicalSort(){
	//본 것 초기화
	int n = adj.size();
	seen = vector<int>(n, 0);
	order.clear();

	for (int i = 0; i < n; ++i)
		//만약 안본게 있다면 바로 봐라 
		if (!seen[i])
			dfs(i);
	//order의 순서를 거꾸로 돌린다
	reverse(order.begin(), order.end());

	//이것의 의미는
	/*
		0 1 0 0
		1 0 0 0
		0 0 0 0
		0 0 0 0
		이렇게 있다면 (2,1) 지역이 1 이라는 것, 즉 왼 아래쪽 부분이 존재한다는 것을 의미한다.
		이것은 역방향 간선이 있다는 것을 의미한다
	*/
	for (int i = 0; i < n; ++i){
		for (int j = i+1; j < n; ++j)
			if (adj[order[j]][order[i]])
				return vector<int>();
	
	}
	return order;

}



int main(void)
{
	int Test_Case;
	int N,j;
	string words[1000];
	vector<int> output;


//	freopen("input.txt", "r", stdin);
	scanf("%d", &Test_Case);

	for (int i = 1; i <= Test_Case; ++i){
		j = 0;
		scanf("%d", &N);

		for (j = 0; j < N; ++j)
			cin >> words[j];

		makeGraph(words,N);
		output = topologicalSort();
		
		if (output.size() == 0)
			printf("INVALID HYPOTHESIS\n");
		else{
			for (int i = 0; i < 26; ++i)
				printf("%c", output[i]+'a');
			printf("\n");
		}


	}

	

	return 0;
}

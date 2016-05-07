//#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;


vector<vector<int>> adj;
vector<string> graph[26][26];
vector<int> indegree, outdegree;




bool checkEuler(){
	int plus1 = 0;
	int minus1 = 0;
	for (int i = 0; i < 26; ++i){
		//각 알파벳 갯수가 짝수거나 outdegree,indegree차이가 1이야해
		int delta = outdegree[i] - indegree[i];
		if (delta < -1 || delta > 1) return false;
		if (delta == 1) plus1++;
		if (delta == -1) minus1++;
	}

	return (plus1==1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}


void getEulerCircuit(int here, vector<int>& circuit){
	for (int there = 0; there < adj.size(); ++there){
		while (adj[here][there] > 0){
			adj[here][there]--;
			getEulerCircuit(there, circuit);
		}
	}
	circuit.push_back(here);
}



//여기서 오류가 있는거를 다 제거 한다
vector<int> getTrailOrCircuit(){
	vector<int> circuit;

	//시작점은 indegree가 outdegree보다 1 많으면 시작점이다
	for (int i = 0; i < 26; ++i){
		if (outdegree[i] == indegree[i] + 1){
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}
	
	for (int i = 0; i < 26; ++i){
		if (outdegree[i]){
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}
	//다 없으면 빈거 내보낸다
	return circuit;
}


void makeGraph(const vector<string>& words){
	
	//그래프를 만들기 전에 모든 것 초기화
	//adj는 단어의 처음과 끝이 있다 없다만 나타내게 하는 것
	//indegree는 단어의 마지막, outdegree는 단어의 처음을 나타내는 것
	adj = vector<vector<int>>(26, vector<int>(26, 0));
	indegree = vector<int>(26, 0);
	outdegree = vector<int>(26, 0);

	for (int i = 0; i < 26; ++i)
		for (int j = 0; j < 26; ++j){
			graph[i][j].clear();
		}


	for (int i = 0; i < words.size(); i++){
		int a = words[i][0] -'a';
		int b = words[i][words[i].size()-1]-'a';
		//printf("%c\n", b + 'a');
		graph[a][b].push_back(words[i]);
		adj[a][b]++;
		outdegree[a]++;
		indegree[b]++;
	}

}


string solve(const vector<string>& words) {
	makeGraph(words);
	// 차수가 맞지 않으면 실패!
	if (!checkEuler()) return "IMPOSSIBLE";
	// 오일러 서킷이나 경로를 찾아낸다
	vector<int> circuit = getTrailOrCircuit();
	// 모든 간선을 방문하지 못했으면 실패!
	if (circuit.size() != words.size() + 1) return "IMPOSSIBLE";

	// 아닌 경우 방문 순서를 뒤집은 뒤 간선들을 모아 문자열로 만들어 반환한다.
	reverse(circuit.begin(), circuit.end());
	string ret;
	for (int i = 1; i < circuit.size(); i++) {
		int a = circuit[i - 1], b = circuit[i];
		if (ret.size()) ret += " ";
		ret += graph[a][b].back();
		graph[a][b].pop_back();
	}
	return ret;

}

int main(void)
{
	int Test_Case;
	int N;
	string temp;
	vector<string> words;

//	freopen("input.txt", "r", stdin);

	scanf("%d", &Test_Case);
	for (int i = 1; i <= Test_Case; ++i){
		words.clear();
		indegree.clear();
		outdegree.clear();
		adj.clear();
		
		//getline 을 하기 위해 \n을 해놓는다
		scanf("%d\n", &N);

		for (int i = 1; i <= N; ++i){
			//string은 getline을 통해 받는다
			getline(cin, temp, '\n');
			words.push_back(temp);
		}
		/*
		makeGraph(words);

		if (!checkEuler()){
			 printf("IMPOSSIBLE\n");
			 continue;
		}

		vector<int> circuit = getTrailOrCircuit();
		if (circuit.size() != words.size() + 1){
			printf("IMPOSSIBLE\n");
			continue;
		}

		reverse(circuit.begin(), circuit.end());
		string ret;
		for (int i = 1; i < circuit.size(); i++){
			int a = circuit[i - 1], b = circuit[i];
			if (ret.size()) ret += " ";
			ret += graph[a][b].back();
			graph[a][b].pop_back();
		}

		*/

		temp = solve(words);
		printf("%s\n", temp.c_str());
	}



	return 0;
}

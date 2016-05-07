//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>
#include <string.h>
using namespace std;


const int ALPHABETS = 26;

int toNumber(char ch) { return ch - 'A'; }


struct TrieNode{
	TrieNode* children[ALPHABETS];				//알파벳만큼의 자식들 생성
	int terminal;								//끝인가 아닌가를 나타내주는 변수
	int first;
	TrieNode() : terminal(-1){ 
		memset(children, 0, sizeof(children));
		first = -1;
	}
	~TrieNode(){
		for (int i = 0; i < ALPHABETS; ++i)
			if (children[i])
				delete children[i];
	}
	
	//입력하는 함수 key, id
	void insert(const char* key, int id){
		if (first == -1) first = id;
		if (*key == 0)
			terminal = id;
		else{
			int next = toNumber(*key);
			if (children[next] == NULL)
				children[next] = new TrieNode();
			children[next]->insert(key + 1, id);
		}
	}

	int type(const char* key, int id){
		if (*key == 0) return 0;				//끝이라면 0 리턴 
		if (first == id) return 1;				//만약 찾는 것이 같다면 1로 리턴
		int next = toNumber(*key);
		return 1 + children[next]->type(key + 1, id);
	}

	TrieNode* find(const char* key){
		if (*key == 0) return this;
		int next = toNumber(*key);
		if (children[next] == NULL) return NULL;
		return children[next]->find(key + 1);
	}


};

int countKeys(TrieNode* trie, const char* word){
	TrieNode* node = trie->find(word);
	if (node == NULL || node->terminal == -1) return strlen(word);
	return trie->type(word, node->terminal);
}


//몇 개의 사전 만들건지 나타내는 함수
TrieNode* readInput(int words){
	vector < pair<int, string> > input;
	for (int i = 0; i < words; ++i){
		char buf[11];
		int freq;
		scanf("%s%d", buf, &freq);
		//printf("%s\n", buf);
		input.push_back(make_pair(-freq, buf));
	}
	sort(input.begin(), input.end());					//미리 정렬해 놓음으로써 순서 상관 없게 만듬
	TrieNode* trie = new TrieNode();
	for (int i = 0; i < input.size(); ++i)
		trie->insert(input[i].second.c_str(), i);			
	trie->first = -1;									//트리의 처음은 first
	return trie;

}


int main(void)
{
	int Test_Case;
	int M, N;				//M is the number of word included dic  ,N is the number of word to input
	char str[11];

	int result; 


	//freopen("input.txt", "r", stdin);		//읽어 들이기 위한

	scanf("%d", &Test_Case);
	for (int i = 1; i <= Test_Case; ++i){
		struct TrieNode *trie;	//트리를 만듬
		result = 0;
		scanf("%d%d", &N, &M);				//input M,N

		trie = readInput(N);				// N개의 readInput 

		
		for (int i = 0; i < M; i++){
			scanf("%s", str);
			result += countKeys(trie, str);
			memset(str, 0, sizeof(str));
		}

		result += M - 1;

		printf("%d\n", result);	
		delete trie;
	}



	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

map<vector<int>, int> toSort;

//미리 1~8 를 다 계산 해 두는 것
void precalc(int n){
	vector<int> perm(n);
	//perm 0 1 2 3 4 5 6 7 로 설정
	for (int i = 0; i < n; ++i)
		perm[i] = i;
	queue<vector<int>> q;
	q.push(perm);
	//map을 이용한 것
	toSort[perm] = 0;
	//queue에 다 나갈 때까지 돌려라
	while (!q.empty()){
		vector<int> here = q.front();
		q.pop();
		//지금의 cost를 기억해두고
		int cost = toSort[here];
	
		for (int i = 0; i < n; i++){
			for (int j = i + 2; j <= n; ++j){
				reverse(here.begin() + i, here.begin() + j);
				//map의 count는 map에 ()안에 있는 값이 있는지 없는지 0, 1 로 나타내준다
				if (toSort.count(here) == 0){
					toSort[here] = cost + 1;
					q.push(here);
				}
				reverse(here.begin() + i, here.begin() + j);
			}
		}
	}

}


int solve(const vector<int>& perm){
	//들어온 perm을 0 ~ n-1 으로 바꾸는 것
	//예를 들어 3 4 1 2 라면 1 0 3 2 형식으로 바꾸는 것
	int small;
	int n = perm.size();
	vector<int> fixed(n);
	for (int i = 0; i < n; ++i){
		small = 0;
		for (int j = 0; j < n; ++j){
			//perm의 i 번째 숫자가 배열에서 상대적으로 몇 순위 인지 나타내는 것
			if (perm[j] < perm[i])
				small++;
		}
		fixed[i] = small;
	}

	//상대적인 숫자를 가지고 precalc에서 미리 전처리 해놨던 것 중에서 찾아서 return
	return toSort[fixed];
}


int main(void)
{
	int Test_Case;
	int num;
	int tmpNum;
	int result;
	vector<int> temp;

//	freopen("input.txt", "r", stdin);

	for (int i = 1; i <= 8; ++i)
		precalc(i);
	
	scanf("%d", &Test_Case);
	for (int i = 1; i <= Test_Case; ++i){
		//toSort.clear();
		temp.clear();
		scanf("%d", &num);
		//precalc(num);
		for (int i = 0; i < num; ++i){
			scanf("%d", &tmpNum);
			temp.push_back(tmpNum);
		}
		result = solve(temp);
		printf("%d\n", result);
	}


	return 0;
}

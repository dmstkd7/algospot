#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <memory.h>
using namespace std;

bool isFriend[10][10];
bool checkNum[10];
int N,M, cnt;


void recusive(){

	bool finish = true;
	int i;
	//먼저 짝이 되지 않은 학생 중 최신의 사람을 찾는다
	for (i = 0; i < N; i++){
		if (checkNum[i] == false){
			finish = false;
			break;
		}
	}
	//만약 짝이 다 있다면 cnt을 하나 증가시키고 return한다
	if (finish){
		cnt++;
		return;
	}

	int fix_start = i;
	checkNum[fix_start] = true;
	for (int j = fix_start + 1; j < N; j++)
		if (!checkNum[j] && isFriend[fix_start][j]){
			checkNum[fix_start] = checkNum[j] = true;
			recusive();
			checkNum[fix_start] = checkNum[j] = false;
		}
	checkNum[fix_start] = false;
			
}


void solve(){
	

	int tmp1, tmp2;
	scanf("%d%d", &N, &M);
	for (int i = 0; i < M; i++){
		scanf("%d%d", &tmp1, &tmp2);
		isFriend[tmp1][tmp2] = true;
		isFriend[tmp2][tmp1] = true;
	}
	recusive();
	printf("%d\n", cnt);

	return;
}



int main(){

	int test_case;
	scanf("%d", &test_case);

	for (int i = 1; i <= test_case; i++){
		memset(checkNum, false, sizeof(checkNum));
		memset(isFriend, false, sizeof(isFriend));
		cnt = 0;
		solve();
	}
	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <memory.h>
using namespace std;

int three[10001];
int four[10001];
int five[10001];
char s[10005];
int num[10005];
int dp[10005];
const int INF = 987654321;

int getSum(int start, int step) {
	int type = INF;
	
	//다 같은지 확인
	for (int i = start; i < start + step-1; i++) {
		if (num[i] != num[i + 1]) {
			type = -1;
			break;
		}	
	}
	if (type != -1) return 1;
	type = INF;
	
	for (int i = start; i < start + step - 2; i++) {
		if ( num[i] - num[i + 1] != num[i + 1] - num[i + 2] ) {
			type = -1;
			break;
		}
	}
	if (type != -1 && abs(num[start]-num[start+1])==1) return 2;
	type = INF;
	

	for (int i = start; i < start + step - 2; i++) {
		if (num[i] - num[i + 1] != -(num[i + 1] - num[i + 2])) {
			type = -1;
			break;
		}
	}
	if (type != -1) return 4;
	type = INF;

	for (int i = start; i < start + step - 2; i++) {
		if (num[i] - num[i + 1] != num[i + 1] - num[i + 2]) {
			type = -1;
			break;
		}
			
	}
	if (type != -1) return 5;

	return 10;
}

//288109756659334461284756482337867831652
int main(void) {

	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		int len=1;
		memset(three, 0, sizeof(three));
		memset(four, 0, sizeof(four));
		memset(five, 0, sizeof(five));
		memset(s, 0, sizeof(s));
		memset(num, 0, sizeof(num));
		for (int i = 0; i < 10001; i++)
			dp[i] = INF;

		scanf("%s", &s[1]);
		while (s[len]) {
			num[len] = s[len] - 'a';
			len++;
		}
	
		for (int i = 1; i <= len-3; i++) {
			three[i] = getSum(i, 3);
			//printf("three : %d\n", three[i]);
		}

		for (int i = 1; i <= len - 4; i++) {
			four[i] = getSum(i, 4);
			//("four : %d\n", four[i]);
		}

		for (int i = 1; i <= len - 5; i++) {
			five[i] = getSum(i, 5);
			//printf("five : %d \n", five[i]);
		}
		
		dp[3] = three[1];
		dp[4] = four[1];
		dp[5] = five[1];

		for (int i = 6; i < len; i++) {
			dp[i] = min(dp[i], dp[i - 3] + three[i - 2]);
			dp[i] = min(dp[i], dp[i - 4] + four[i - 3]);
			dp[i] = min(dp[i], dp[i - 5] + five[i - 4]);
		}
		
		printf("%d\n", dp[len-1]);

	}



	return 0;
}

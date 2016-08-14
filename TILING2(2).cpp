#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <memory.h>
#define MOD 1000000007
using namespace std;

int dp[101];


int go(int n) {

	int& ret = dp[n];
	if (ret != -1) return dp[n];
	ret = (go(n - 1) + go(n - 2)) % MOD;
	return ret;
}

int main(void) {

	
	int n,t;
	scanf("%d", &n);
	memset(dp, -1, sizeof(dp));
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 0; i < n; i++) {
		scanf("%d", &t);
		printf("%d\n", go(t));
	}


	return 0;
}

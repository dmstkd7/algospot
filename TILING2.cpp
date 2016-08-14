#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#define MOD 1000000007
using namespace std;

int main(void) {

	int dp[101];
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= 100; i++)
		dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
	
	int n,t;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &t);
		printf("%d\n", dp[t]);
	}


	return 0;
}

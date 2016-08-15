#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <memory.h>
#define MOD 1000000007
using namespace std;

int dp[101];
int asy[101];

void precalc() {
	
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= 100; i++) {
		dp[i] = (dp[i - 1] + dp[i - 2]) % MOD;
	}
	asy[1] = 1;
	asy[2] = 2;
	for (int i = 3; i <= 100; i++) {
		if (i % 2)
			asy[i] = dp[i / 2] % MOD;
		else
			asy[i] = ( dp[i / 2] + dp[(i / 2) - 1 ] ) % MOD;
	}
	
	
}

int main(void) {

	int test_case, n;
	scanf("%d", &test_case);
	precalc();
	while (test_case--) {
		scanf("%d", &n);
		printf("%d\n", (dp[n] - asy[n]+ MOD) % MOD);
	}

	return 0;
}

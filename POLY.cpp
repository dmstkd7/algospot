#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <memory.h>
#define MOD 10000000
using namespace std;

const int INF = 987654321;
int cache[101][101];


int poly(int n, int first) {

	if (n == first) return 1;
	int& ret = cache[n][first];
	if (ret != -1) return ret;
	
	ret = 0;
	for (int second = 1; second <= n - first; second++) {
		ret += (  (first + second - 1) * poly(n - first, second) ) % MOD;
		ret %= MOD;
	}
	
	return ret;
}


int main(void) {

	int test_case, block, ans;
	scanf("%d", &test_case);
	while (test_case--) {
		ans = 0;
		memset(cache, -1, sizeof(cache));
		scanf("%d", &block);
		
		for (int first = 1; first <= block; first++) {
			ans += poly(block, first);
			ans %= MOD;
		}
			
		printf("%d\n", ans);
	}
	


	return 0;
}

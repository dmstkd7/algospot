#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <memory.h>
#include <algorithm>
typedef long long int lld;
using namespace std;

lld dp[101][101], a[2][101];
int n1, n2;
const long long NEGINF = numeric_limits<long long>::min();

lld lis(int A, int B) {
	
	lld& ret = dp[A][B];
	if (ret != -1) return ret;

	ret = 2;
	lld maxValue = max<lld>(a[0][A], a[1][B]);
	//printf("%lld\n", maxValue);

	for (int nextA = A + 1; nextA <= n1; nextA++)
		if (maxValue < a[0][nextA])
			ret = max<lld>(ret, lis(nextA, B) + 1);
		
	for (int nextB = B + 1; nextB <= n2; nextB++)
		if (maxValue < a[1][nextB])
			ret = max<lld>(ret, lis(A, nextB) + 1);

	return ret;
			
}


int main(void) {

	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {

		for (int i = 0; i <= 100; i++)
			for (int j = 0; j <= 100; j++)
				dp[i][j] = -1;
		memset(a, 0, sizeof(a));

		scanf("%d%d", &n1, &n2);
		for (int i = 1; i <= n1; i++)
			scanf("%lld", &a[0][i]);
		for (int i = 1; i <= n2; i++)
			scanf("%lld", &a[1][i]);
		a[0][0] = NEGINF;
		a[1][0] = NEGINF;
	//	printf("%lld", a[0][0]);
		printf("%lld\n", lis(0, 0)-2);

	}



	return 0;
}

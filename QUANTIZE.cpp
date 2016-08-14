#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <memory.h>
using namespace std;

int a[101];
int sum[101], sqSum[101], dp[101][11];
int n;
const int INF = 987654321;


int getMinimum(int start, int finish) {
	int sm = sum[finish] - (start==0? 0 : sum[start - 1]);
	int sqsm = sqSum[finish] - (start==0? 0: sqSum[start - 1]);
	int m = int(0.5 + ((double)sm / (finish - start + 1)));
	int ret = sqsm - 2 * m * sm + m*m * (finish - start + 1);
	//printf("sm : %d  sqsm: %d  m: %d ret: %d \n", sm, sqsm, m, ret);
	return ret;
}


int go(int start, int parts) {

	if (start == n) return 0;
	if (parts == 0) return INF;

	int& ret = dp[start][parts];
	if (ret != -1) return ret;

	ret = INF;

	for (int i = start; i + 1 <= n; i++) {
		ret = min(ret, getMinimum(start, i) + go(i + 1, parts - 1));
		//printf("start : %d ret:  %d \n", start, ret);
	}
	return ret;
}


void precalc(int start, int finish) {
	sort(a, a + finish);

	sum[0] = a[0];
	sqSum[0] = a[0] * a[0];

	for (int i = 1; i < finish; i++) {
		sum[i] = sum[i - 1] + a[i];
		sqSum[i] = sqSum[i - 1] + a[i] * a[i];
		//printf("%d %d\n", sum[i], sqSum[i]);
	}
}

int main(void) {
	int test_case, parts;
	scanf("%d", &test_case);
	while (test_case--) {
		memset(a, 0, sizeof(a));
		memset(sum, 0, sizeof(sum));
		memset(sqSum, 0, sizeof(sqSum));
		memset(dp, -1, sizeof(dp));
		scanf("%d%d", &n, &parts);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);

		precalc(0, n);

		printf("%d\n", go(0, parts));

	}

 	return 0;
}

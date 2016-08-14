#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <memory.h>
#include <algorithm>
using namespace std;

const int INF = 987654321;
int a[101][101];
int dp[101][101];
int n;


int go(int y, int x) {

	int& ret = dp[y][x];
	if (ret != -1) return ret;
	
	if (y == n) return 1;
	//가장 큰 것을 구하자
	
	ret = 0;
	if (a[y + 1][x] > a[y + 1][x + 1])
		ret += go(y + 1, x);
	else if (a[y + 1][x] < a[y + 1][x + 1])
		ret += go(y + 1, x + 1);
	else
		ret += go(y + 1, x + 1) + go(y + 1, x);

	return ret;
}


int main(void) {

	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		memset(a, 0, sizeof(a));
		memset(dp, -1, sizeof(dp));
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= i; j++) {
				scanf("%d", &a[i][j]);
			}
		}
		for (int i = n-1; i >= 1; i--) {
			for (int j = i; j >=1; j--) {
				int add = max(a[i + 1][j +1], a[i + 1][j]);
				a[i][j] += add;
			}
		}
		
		//path를 일단 만들자
		printf("%d\n", go(1, 1));


	}

	return 0;
}

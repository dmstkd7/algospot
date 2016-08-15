#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <memory.h>
using namespace std;

const int MAX_V = 1001;

double dp[MAX_V][2 * MAX_V + 1];
int day, want;


double predict(int days, int climb) {

	if (days == day) return climb >= want ? (double)1 : 0;
	double& ret = dp[days][climb];
	if (ret != -1.0) return ret;
	ret = 0.75 * predict(days + 1, climb + 2) + 0.25 * predict(days + 1, climb + 1);
	return ret;
}

int main(void) {

	int test_case;
	scanf("%d", &test_case);
	while (test_case--) {
		for (int i = 0; i < MAX_V; i++)
			for (int j = 0; j < 2 * MAX_V; j++)
				dp[i][j] = -1.0;
		scanf("%d%d", &want, &day);
		printf("%0.10f\n", predict(0,0));
	}

	return 0;
}

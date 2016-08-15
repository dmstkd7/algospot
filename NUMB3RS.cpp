#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <memory.h>
using namespace std;


double cache[51][101];
int graph[51][51];
int day, city, n, start;

double go(int pos, int days) {

	if (days == day) return (pos == n ? 1 : 0);
	double& ret = cache[pos][days];
	if (ret != -1.0) return ret;


	ret = 0;
	int cnt = 0;
	double tmp = 0;
	for (int i = 0;  i< city; i++) {
		if (graph[i][pos] == 1) {
			ret += go(i, days + 1);
			cnt++;
		}
	}

	ret /= (double)cnt;

	return ret;
}


int main(void) {

	int test_case, res;
	scanf("%d", &test_case);
	while (test_case--) {
		memset(graph, 0, sizeof(graph));
		for (int i = 0; i <= 50; i++) {
			for (int j = 0; j <= 100; j++) {
				cache[i][j] = -1.0;
			}
		}
		scanf("%d%d%d", &city, &day, &start);
		for (int i = 0; i < city; i++) {
			for (int j = 0; j < city; j++) {
				scanf("%d", &graph[i][j]);
			}
		}

		scanf("%d", &res);
		for (int i = 0; i < res; i++) {
			//cache 초기화
			for (int i = 0; i <= 50; i++) {
				for (int j = 0; j <= 100; j++) {
					cache[i][j] = -1.0;
				}
			}
			scanf("%d", &n);
			printf("%0.10f ", go(start, 0));
		}
		printf("\n");
	}
	
	return 0;
}

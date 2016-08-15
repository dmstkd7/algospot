#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory.h>
using namespace std;

int skip;
int limit = 1000000100;
int bino[201][201];

void precalc() {

	memset(bino, 0, sizeof(bino));
	for (int i = 0; i <= 200; i++) {
		bino[i][0] = bino[i][i] = 1;
		for (int j = 1; j <= i-1; j++) {
			bino[i][j] = min(limit, bino[i - 1][j - 1] + bino[i - 1][j]);
		}
	}
	return;
}


void generate1(int n, int m, string s) {

	if (skip < 0) return;
	
	if (n == 0 && m == 0) {
		if (skip == 0) cout << s << endl;
		skip--;
		return;
	}

	if (skip - bino[n + m][n] >= 0) {
		skip -= bino[n + m][n];
		return;
	}

	if (n > 0) generate1(n - 1, m, s + "-");
	if (m > 0) generate1(n, m - 1, s + "o");
	

}


int main(void) {

	
	int test_case, n, m, k;
	scanf("%d", &test_case);
	precalc();
	while (test_case--) {
		scanf("%d%d%d", &n, &m, &k);
		skip = k-1;
		generate1(n, m, "");

	}

	return 0;
}

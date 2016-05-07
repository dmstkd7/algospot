//#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


vector<int> slice(const vector<int>& v, int a, int b){
	return vector<int>(v.begin() + a, v.begin() + b);
}

void printPostOrder(const vector<int>& preorder, const vector<int>& inorder)
{
	const int N = preorder.size();

	if (preorder.empty()) return;

	const int root = preorder[0];


	const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
	const  int R = N - 1 - L;

	printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
	printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));


	cout << root << ' ';
}


int main(int argc, char** argv) {
	int T;
	int test_case;
	int N;		//배열에 갯수가 몇개 인지
	vector<int> A, B;
	int temp;
	

	setbuf(stdout, NULL);

	scanf("%d", &T);	//Codeground 시스템에서는 C++ 에서도 scanf 사용을 권장합니다.
	for (test_case = 1; test_case <= T; ++test_case) {
		scanf("%d", &N);
		A.clear();
		B.clear();

		for (int j = 1; j <= N; j++)
		{
			scanf("%d", &temp);
			A.push_back(temp);
		}

		for (int j = 1; j <= N; j++)
		{
			scanf("%d", &temp);
			B.push_back(temp);
		}


		printPostOrder(A, B);
		cout << endl;


	}

	return 0;	//	정상종료 시 반드시 0을 리턴해야 합니다.
}

//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


/*
int shift(const string& original, const string& target)
{
	return kmpSearch(original + original, target)[0];
}
*/

//부분 일치 함수
vector<int> getPartialMatch(const string&N){
	int m = N.size();
	vector<int> pi(m, 0);
	int begin = 1, matched = 0;
	while (begin + matched<m){
		if (N[begin + matched] == N[matched]){
			matched++;
			pi[begin + matched - 1] = matched;
		}
		else{
			if (matched == 0)
				begin++;
			else{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}

	return pi;
}


//부분 일치 함수를 이용한 kmp 함수
vector<int> kmpSearch(const string& H, const string& N){
	int n = H.size(), m = N.size();
	vector<int>ret;
	vector<int> pi = getPartialMatch(N);

	int begin = 0, matched = 0;
	while (begin <= n - m){
		if (matched<m && H[begin + matched] == N[matched]){
			matched++;
			if (matched == m) ret.push_back(begin);
		}
		else{
			if (matched == 0)
				begin++;
			else{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}

	return ret;
}



int main(int argc, char** argv) {
	int T;
	int test_case;
	int N;		//배열에 갯수가 몇개 인지
	char temp[10001];
	int num;
	int count = 1;
	vector<int> temp_num;


	//setbuf(stdout, NULL);

	scanf("%d", &T);	//Codeground 시스템에서는 C++ 에서도 scanf 사용을 권장합니다.
	for (test_case = 1; test_case <= T; ++test_case) {
		scanf("%d", &N);
		//A.clear();
		num = 0;
		
		N++;
		vector<string> A(N);
		for (int j = 0; j < N; j++)
		{
			scanf("%s", &temp);
			A[j] = temp;
		}


		int p;
		for (int i = 1; i < N ; i++)
		{
			if (count % 2 == 1){
				temp_num = kmpSearch(A[i] + A[i], A[i - 1]);
				 p = temp_num[0];
				 num += p;
			}
			else{
				temp_num = kmpSearch(A[i - 1] + A[i - 1], A[i]);
				p = temp_num[0];
				num += p;
			}
				
			count++;
		}

		cout << num << endl;
	}

	return 0;	//	정상종료 시 반드시 0을 리턴해야 합니다.
}

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <stack>
using namespace std;


int main(void) {
	
	int n;
	char tmp[10010];
	stack<char> st;
	scanf("%d", &n);
	while (n--) {
		bool isNo = false;
		while (!st.empty())
			st.pop();
		cin >> tmp;
		int length = 0;
		while (tmp[length] != 0)
			length++;
		for (int i = 0; i <length; i++) {
			if (( tmp[i] == ']' || tmp[i] == ')' || tmp[i] == '}' ) && st.empty()) {
				isNo = true;
				break;
			}

			if (tmp[i] == '[' || tmp[i] == '(' || tmp[i] == '{')
				st.push(tmp[i]);
			else {
				if (tmp[i] == ']' && st.top() == '[')
					st.pop();
				else if (tmp[i] == '}' && st.top() == '{')
					st.pop();
				else if (tmp[i] == ')' && st.top() == '(')
					st.pop();
				else {
					isNo = true;
					break;
				}
			}
		}
		if (isNo || !st.empty())
			printf("NO\n");
		else
			printf("YES\n");
	}



	return 0;
}

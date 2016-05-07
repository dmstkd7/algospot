#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string.h>
#include <queue>
using namespace std;


const int MAX_COUNT = 12;
int c[1 << (MAX_COUNT*2)];


int get(int state, int index){
	return (state >> (index * 2)) & 3;
}

//state는 현재 값, index는 몇 번째를 원하는건지 , value는 몇 번째에 무슨 값을 넣을건지 0,1,2,3 중에 선택
int set(int state, int index, int value){
	return (state & ~(3 << index * 2) | (value << index * 2));
}

int sgn(int x){ if (!x) return 0; return x > 0 ? 1 : -1; }

int incr(int x){ if (x < 0) return x - 1; return x + 1; }



int bidir(int discs, int begin, int end){
	
	//예외 처리
	if (begin == end) return 0;
	queue<int> q;
	memset(c, 0, sizeof(c));
	q.push(begin);
	c[begin] = 1;
	q.push(end);
	c[end] = -1;
	while (!q.empty()){
		int here = q.front();
		q.pop();
		int top[4] = { -1, -1, -1, -1 };
		//i가 낮을 수록 top이어야 하므로 11, 10 ...1 이 순서대로 넣음
		for (int i = discs - 1; i >= 0; --i){
			top[get(here, i)] = i;
			//printf("%d %d \n", get(here, i), i);
		}
		for (int i = 0; i < 4; ++i){
			//만약 i번째의 탑이 -1이 아니라면 안에 들어가서 옮겨라
			if (top[i] != -1){
				for (int j = 0; j < 4; ++j){
					//i와 j가 다른건, top[j]가 비어있거나 i보다 j에 있는것이 더 커야한다.
					if (i != j && (top[j] == -1 || top[j] > top[i])){
						int there = set(here, top[i], j);
						//아직 방문하지 않는 곳이라면
						if (c[there] == 0){
							c[there] = incr(c[here]);
							q.push(there);
						}
						else if (sgn(c[there]) != sgn(c[here])){
							//printf("%d %d\n", abs(c[there]), abs(c[here]));
							return abs(c[there]) + abs(c[here]) - 1;
						}
					}
				}
			}
		}
	}
	return -1;
}





int main(void){


	int Test_Case;
	int count,num1, num2;
	int temp,end;
	int result;
	int value_temp;
	

	//freopen("input.txt", "r", stdin);

	scanf("%d", &Test_Case);
	for (int i = 1; i <= Test_Case; ++i){
		temp = 1 << (MAX_COUNT * 2 -1);
		end = 1 << (MAX_COUNT * 2 -1);
		num1 = 0;
		value_temp = 0;
		//먼저 4개의 입력을 받아야 하네
		scanf("%d", &count);
		//count1 = count;

		for (int i = 0; value_temp != 4;){
			scanf("%d", &num1);
			for (int j = 0; j < num1; ++j){
				scanf("%d", &num2);
				temp = set(temp, num2-1, value_temp);
			}
			//i += num1; 안해도 될것 같은데
			value_temp++;
			i += num1;
		}

		//end는 end의 value가 모두 3이어야한다
		for (int i = 0; i < count; ++i){
			end = set(end, i, 3);
		}


		//printf("%d %d\n", temp, end);
		result = bidir(count, temp, end);

		printf("%d\n", result);
		
	}



	return 0;
}

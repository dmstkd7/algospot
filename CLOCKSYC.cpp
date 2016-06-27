#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

int clock[16];

const int type[10][6] = {
	{ 0, 1, 2, -1 },
	{ 3, 7, 9, 11,-1 },
	{ 4, 10, 14, 15, -1 },
	{ 0, 4, 5, 6, 7, -1 } ,
	{ 6, 7, 8, 10, 12 ,-1},
	{ 0, 2, 14, 15, -1 },
	{ 3, 14, 15, -1 },
	{ 4, 5, 7, 14, 15, -1 },
	{ 1, 2, 3, 4, 5, -1 },
	{ 3, 4, 5, 9, 13 ,-1}
};


void changeClock(int counter, int typeNum){
	for (int i = 0; i < counter; i++){
		int j = 0;
		while (type[typeNum][j] != -1){
			//printf("하긴 하냐 %d %d\n", typeNum, j);
			clock[type[typeNum][j]] = clock[type[typeNum][j]] + 3;
			clock[type[typeNum][j]] %= 12;
			j++;
		}
	}
}

bool check(){

	for (int i = 0; i < 16; i++)
		if (clock[i] != 12 && clock[i] != 0){
			return false;
		}
			
			
	return true;
}


int main(){

	int test_case, tmp;
	bool isOk = true;
	int temp[16];
	scanf("%d", &test_case);

	for (int i = 1; i <= test_case; i++){
		
		isOk = true;
		for (int j = 0; j < 16; j++){
			scanf("%d", &clock[j]);
			temp[j] = clock[j];
		}
			


		for (int t1 = 0; t1 < 4; t1++)
			for (int t2 = 0; t2 < 4; t2++)
				for (int t3 = 0; t3 < 4; t3++)
					for (int t4 = 0; t4 < 4; t4++)
						for (int t5 = 0; t5 < 4; t5++)
							for (int t6 = 0; t6 < 4; t6++)
								for (int t7 = 0; t7 < 4; t7++)
									for (int t8 = 0; t8 < 4; t8++)
										for (int t9 = 0; t9 < 4; t9++)
											for (int t10 = 0; t10 < 4; t10++){
												changeClock(t1, 0);
												changeClock(t2, 1);
												changeClock(t3, 2);
												changeClock(t4, 3);
												changeClock(t5, 4);
												changeClock(t6, 5);
												changeClock(t7, 6);
												changeClock(t8, 7);
												changeClock(t9, 8);
												changeClock(t10, 9);
												if (check()){
													printf("%d\n", t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10);
													t1 = t2 = t3 = t4 = t5 = t6 = t7 = t8 = t9 = t10 = 5;
													isOk = false;
													break;
												}
												for (int i = 0; i < 16; i++)
													clock[i] = temp[i];
											}
		
		if (isOk)
			printf("-1\n");
	}
	
	
	return 0;
}

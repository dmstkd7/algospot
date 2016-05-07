//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;


map<int, int> map1;				//맵 사용


typedef struct _Sample{
	int p, q;
}Sample;


bool isDominated(int x, int y){
	map<int, int>::iterator it = map1.lower_bound(x);
	if (it == map1.end()) return false;

	return y < it->second;
	
}

void removeDominated(int x, int y){
	map<int, int>::iterator it = map1.lower_bound(x);
	if (it == map1.begin()) return;
	--it;
	while (true){
		if (it->second > y) break;
		if (it == map1.begin()){
			map1.erase(it);
			break;
		}
		else{
			map<int, int>::iterator jt = it;
			--jt;
			map1.erase(it);
			it = jt;
		}
	}

}

int registered(int x, int y){
	if (isDominated(x, y)) return map1.size();
	removeDominated(x, y);
	map1[x] = y;
	return map1.size();
}

int main(void)
{
	int T;
	int Test_Case;
	int count = 0;
	Sample S;
	//Sample S[10000];
	int temp;
	map <int, int> ::const_iterator m1_Iter, a, b;
	map< int, int >::reverse_iterator r;

	int z;	//방지용

	scanf("%d", &Test_Case);
	for (int i = 1; i <= Test_Case; i++) {
		scanf("%d", &T);							//몇개 테스트 할건지

		for (int i = 0; i < T; i++){					//테스트 입력 받기
			scanf("%d%d", &S.p, &S.q);
			//입력을 받고(먼저 입력을 받을 수 있는지 없는지를 판가름한다.
			//그와 관련 된 것은 다 지워야 한다.
			//그리고 카운트를 한다.
			temp= registered(S.p, S.q);
			
			count += temp;
		}
	

		printf("%d\n", count);
		map1.clear();
		count = 0;
	}

	
	//scanf("%d", &z);


	return 0;
}

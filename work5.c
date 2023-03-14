#include <stdio.h>


struct add {
	int a, b;

};

int main(){
	int sum;

	struct add add;
	struct add test;
	//일부로 다른 변수 이름을 하나 더 추가 해봤습니다.

	add.a = 3;
	test.a = 4;

	sum = add.a + test.a;

	printf("%d",sum);

	return 0;
}

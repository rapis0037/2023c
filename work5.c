#include <stdio.h>


struct add {
	int a, b;

};

int main(){
	int sum;

	struct add add;
	struct add test;
	//�Ϻη� �ٸ� ���� �̸��� �ϳ� �� �߰� �غý��ϴ�.

	add.a = 3;
	test.a = 4;

	sum = add.a + test.a;

	printf("%d",sum);

	return 0;
}

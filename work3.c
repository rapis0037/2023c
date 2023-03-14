#include <stdio.h>

int main(){

	int va[2] = { 3,4 }, sum;

	puts("두 수를 초기화 해주세요");
	scanf("%d %d", &va[0], &va[1]);
	sum = va[0] + va[1];
	printf("%d", sum);

	return 0;
}

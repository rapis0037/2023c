#include <stdio.h>

int main(){

	int va[2] = { 3,4 }, sum;

	puts("배열을 초기화하세요");
	scanf("%d %d", &va[0], &va[1]);
	sum = va[0] + va[1];
	printf("%d", sum);

	return 0;
}

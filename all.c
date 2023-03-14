#include <stdio.h>

struct fun {
	int a, b;


};



int main(){
	
	int a[2] = { 3,4 }, b, c, d = 3, e = 4, sum;// d와 e에 3, 4를 넣어서 과제 1을 만족시켰습니다.
	struct fun ma;
	FILE* fp;
	fp = fopen("my.txt", "r");

	fscanf(fp, "%d", &b);
	fscanf(fp, "%d", &c);
	ma.a = b;
	ma.b = c;
	//구조체에 있는 두 변수에 my.txt 파일에 있는 3과 4를 넣어서 과제 4, 5의 조건을 만족시켰습니다.
	
	fclose(fp);

	puts("배열을 초기화 시켜주세요");
	scanf("%d", &a[0]);
	scanf("%d", &a[1]);
	// 배열 a를 초기화시켜 과제 3을 만족시켰습니다.

	puts("두 수를 입력해주세요");
	scanf("%d", &b);
	scanf("%d", &c);
	// b와 c를 scanf로 초기화하여 과제 2을 만족시켰습니다.

	sum = ma.a + ma.b + a[0] + a[1] + b + c + d + e;
	printf("%d", sum);


	return 0;
}

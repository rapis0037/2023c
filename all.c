#include <stdio.h>

struct fun {
	int a, b;


};



int main(){
	
	int a[2] = { 3,4 }, b, c, d = 3, e = 4, sum;// d�� e�� 3, 4�� �־ ���� 1�� �������׽��ϴ�.
	struct fun ma;
	FILE* fp;
	fp = fopen("my.txt", "r");

	fscanf(fp, "%d", &b);
	fscanf(fp, "%d", &c);
	ma.a = b;
	ma.b = c;
	//����ü�� �ִ� �� ������ my.txt ���Ͽ� �ִ� 3�� 4�� �־ ���� 4, 5�� ������ �������׽��ϴ�.
	
	fclose(fp);

	puts("�迭�� �ʱ�ȭ �����ּ���");
	scanf("%d", &a[0]);
	scanf("%d", &a[1]);
	// �迭 a�� �ʱ�ȭ���� ���� 3�� �������׽��ϴ�.

	puts("�� ���� �Է����ּ���");
	scanf("%d", &b);
	scanf("%d", &c);
	// b�� c�� scanf�� �ʱ�ȭ�Ͽ� ���� 2�� �������׽��ϴ�.

	sum = ma.a + ma.b + a[0] + a[1] + b + c + d + e;
	printf("%d", sum);


	return 0;
}

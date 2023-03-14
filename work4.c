#include <stdio.h>

int main(){

	int a,b,c;
	FILE* fp;

	fp = fopen("my.txt","r");

	fscanf(fp, "%d", &a);
	fscanf(fp, "%d", &b);

	c = a + b;

	fclose(fp);

	printf("%d", c);

	return 0;
}

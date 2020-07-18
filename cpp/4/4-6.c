#include<stdio.h>
int main()
{
	char y[30];
	char m[30];
	int i,j;
	scanf("%s %s",y,m);
	i=strlen(y);
	j=strlen(m);
	printf("%*d %*d",i,i,j,j);
}


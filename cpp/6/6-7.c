#include<stdio.h>
int main()
{
	char h[50];
	int n,m;
	scanf("%s",&h);
	n=strlen(h);
	for(m=n-1;m>=0;m--)
		printf("%c",h[m]);
}

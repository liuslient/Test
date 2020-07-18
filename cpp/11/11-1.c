#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void hs(char *h,int n);
void hs(char *h,int n)
{
	int j;
	printf("请输入字母");
	for(j=0;j<=n;j++)
	{
		h[j]=getchar();
	}
	return 0;
}
int main()
{
	char h[100];
	int n=0,i;
	printf("请输入数字");
	scanf("%d",&n);
	hs(h,n);
	for(i=0;i<=n;i++)
	{
		printf("%c",h[i]);
	}
}

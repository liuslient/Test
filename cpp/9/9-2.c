#include<stdio.h>
void chline(char ch,int i,int j)
{
	int n,m;
	for(n=0;n<j;n++)
	{
		for(m=0;m<i;m++)
		{
			putchar(ch);
		}
		printf("\n");
	}
}
int main()
{
	char c;
	int i,j;
	printf("输入指定字符串:\n");
	scanf("%c",&c);
	printf("输入几行几列:\n");
	scanf("%d %d",&i,&j);
	chline(c,i,j);
}

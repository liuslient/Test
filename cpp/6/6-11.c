#include<stdio.h>
int main()
{
	int h[8];
	int i;
	for(i=0;i<8;i++)
		scanf("%d",&h[i]);
	for(i=7;i>=0;i--)
		printf("%d ",h[i]);
}

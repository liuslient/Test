#include<stdio.h>
#include<stdlib.h>
int main()
{
	int h[100];
	int i,j,t;
	for(i=0;i<100;i++)
	{
		h[i]=rand()%10+1;
	}
	printf("生成的随机数:\n");
	for(i=0;i<100;i++)
	{
		printf("%d ",h[i]);
	}
	printf("\n");
	for(i=0;i<100;i++)
	{
		for(j=i;j<100;j++)
		{
			if(h[i]<h[j])
			{
				t=h[i];
				h[i]=h[j];
				h[j]=t;
			}
		}
	}
	printf("排序后的随机数：\n");
	for(i=0;i<100;i++)
	{
		printf("%d ",h[i]);
	}
	printf("\n");
}

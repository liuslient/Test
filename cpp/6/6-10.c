#include<stdio.h>
int main()
{
	int n,m,i,w=0;
	printf("请输入两个数字:");
	scanf("%d %d",&n,&m);
	while(m>n)
	{
		for(i=n;i<=m;i++)
		{
			w+=i*i;
		}
		printf("The sums of the squares from %d to %d is %d\n",n*n,m*m,w);
		printf("请输入两个数字:");
		scanf("%d %d",&n,&m);
		w=0;

	}
}

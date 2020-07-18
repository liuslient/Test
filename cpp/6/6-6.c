#include<stdio.h>
int main()
{
	int n,m;
	int i,j,k;
	scanf("%d %d",&n,&m);
	for(i=n;i<=m;i++)
	{
		j=i*i;
		k=i*i*i;
		printf("%d   %d   %d\n",i,j,k);
	}
}

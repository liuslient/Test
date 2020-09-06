#include<stdio.h>
int main()
{
	int n,m,i,w=0;
	int h[100];
	while(scanf("%d",&n)!=EOF&&n!=0)
	{
		w=0;
		for(i=0;i<n;i++)
		{
			scanf("%d",&h[i]);
			w+=h[i];
		}
		printf("%d\n",w);
	}
}

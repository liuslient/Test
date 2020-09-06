#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
int dp[10000];
int w[10000];
int h[10000];
int main(){
	int n,m,t,i,j;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d %d",&n,&m);
		for(i=0;i<n;i++)
		{
			scanf("%d",&h[i]);
		}
		for(i=0;i<n;i++)
		{
			scanf("%d",&w[i]);
		}
		memset(dp,0,sizeof(dp));
		for(i=0;i<n;i++)
		{
			for(j=m;j>=w[i];--j)
			{
				dp[j]=max(dp[j],dp[j-w[i]]+h[i]);
			}
		}
		printf("%d\n",dp[m]);
	}
	return 0;
}


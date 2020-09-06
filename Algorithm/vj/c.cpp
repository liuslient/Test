#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int v[500],m[500],dp[500][10006];
int main()
{
	int t,a,b,i,j,n;
	scanf("%d",&t);
	while(t--)
	{
		memset(v,0,sizeof(v));
		memset(m,0,sizeof(m));
		memset(dp,0,sizeof(dp));
		scanf("%d %d",&a,&b);
		scanf("%d",&n);
		for(i=1;i<=n;i++)
		{
			scanf("%d %d",&v[i],&m[i]);
		}
		for(i=0;i<=n;i++)
		{
			for(j=0;j<=b-a;j++)
				dp[i][j]=100000;
		}
		dp[0][0]=0;
		for(i=1;i<=n;i++)
		{
			for(j=0;j<=b-a;j++)
			{
				if(m[i]>j)
				{
					dp[i][j]=dp[i-1][j];
				}
				else
				{
					dp[i][j]=min(dp[i-1][j],dp[i][j-m[i]]+v[i]);
				}
			}
		}
		if(dp[n][b-a]==100000)
		{
			printf("This is impossible.\n");
		}
		else
		printf("The minimum amount of money in the piggy-bank is %d.\n",dp[n][b-a]);
	}
	return 0;
}

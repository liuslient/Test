#include <iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
using namespace std;
int main()
{
    int n,m,i,j;
    cin>>n>>m;
    long long int dp[n+10][m];
    memset(dp,0,sizeof(dp));
    dp[1][0]=dp[1][1]=1;
    for ( i = 2; i <= n+1; i++)
    {
        for ( j = 0; j < m; j++)
        {
            dp[i][0]+=dp[i-1][j];
        }
        for ( j = 0; j <= m-2; j++)
        {
            dp[i][j+1]=dp[i-1][j];
        }
        
    }
    cout<<dp[n+1][0];
    
    
}
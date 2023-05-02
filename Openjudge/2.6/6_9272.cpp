#include <iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
using namespace std;
int main()
{
    int n,m,i,j;
    cin>>n;
    int dp[n+10][2];
    dp[1][1]=1;
    dp[1][0]=8;
    for ( i = 2; i <= n; i++)
    {
        dp[i][0]=dp[i-1][0]*9+dp[i-1][1]*1;
        dp[i][1]=dp[i-1][0]*1+dp[i-1][1]*9;
        dp[i][0]%=12345;
        dp[i][1]%=12345;
    }

    cout<<dp[n][0];
    
    
}
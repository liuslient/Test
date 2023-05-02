#include <iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
using namespace std;
int main()
{
    int n,i;
    cin>>n;
    int dp[n+10][3];
    dp[1][0]=dp[1][2]=dp[1][1]=1;
    for ( i = 2; i <= n; i++)
    {
        dp[i][0]=dp[i-1][0]+dp[i-1][2]+dp[i-1][1];
        dp[i][2]=dp[i-1][0]+dp[i-1][2];
        dp[i][1]=dp[i-1][0]+dp[i-1][1];
        dp[i][0]%=12345;
        dp[i][1]%=12345;
        dp[i][2]%=12345;
    }
    cout<<(dp[n][0]+dp[n][1]+dp[n][2])%12345;
    
}
#include<bits/stdc++.h>
using namespace std;
const int Mn=10000005;
long long n,m,dp[Mn],c[Mn],v[Mn];
int main()
{
    memset(dp,99,sizeof(dp));
    dp[0]=0;
    cin>>m;
    for(int i=1;i*i*i*i<=m;i++){
        c[i]=i*i*i*i;
        n=i;
    }
    for(int i=1;i<=n;i++){
        for(int j=c[i];j<=m;j++){
            dp[j]=min(dp[j],dp[j-c[i]]+1);
        }
    }
    cout<<dp[m];
}
#include<bits/stdc++.h>
using namespace std;
const int Mn=10000005;
long long n,m,dp[Mn],c[Mn],v[Mn];
int main()
{
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        cin>>c[i]>>v[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=c[i];j<=m;j++){
            dp[j]=max(dp[j],dp[j-c[i]]+v[i]);
        }
    }
    cout<<dp[m];
}
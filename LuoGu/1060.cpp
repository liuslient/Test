#include<bits/stdc++.h>
using namespace std;
const int Mn=30;
int n,m,c[Mn],v[Mn],dp[30005];
int main()
{
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        cin>>c[i]>>v[i];
        v[i]=v[i]*c[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=m;j>=c[i];j--){
            dp[j]=max(dp[j],dp[j-c[i]]+v[i]);
        }
    }
    cout<<dp[m];
}
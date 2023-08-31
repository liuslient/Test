#include<bits/stdc++.h>
using namespace std;
const int Mn=30;
int n,m,c,dp[30005]={1};
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>c;
        for(int j=m;j>=c;j--){
            dp[j]=dp[j]+dp[j-c];
        }
    }
    cout<<dp[m];
}
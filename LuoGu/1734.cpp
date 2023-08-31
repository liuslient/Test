#include<bits/stdc++.h>
using namespace std;

int n,m,c[1010],v[1010],dp[1005];
int main()
{
    cin>>n;
    m=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            if(i%j==0){
                v[i]+=j;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=m;j>=i;j--){
            dp[j]=max(dp[j],dp[j-i]+v[i]);
        }
    }
    cout<<dp[m];
}
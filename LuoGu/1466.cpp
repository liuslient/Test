#include<bits/stdc++.h>
using namespace std;
const int Mn=30;
int n;
long long dp[800]={1};
int main()
{
    cin>>n;
    int m=n*(n+1)/2;
    if(m%2==1){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=n;i++){
        for(int j=m;j>=i;j--){
            dp[j]=dp[j]+dp[j-i];
        }
    }
    cout<<dp[m/2]/2;
}
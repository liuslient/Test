#include<bits/stdc++.h>
using namespace std;

int V,N,M,c[100010],dp[100010],v[10010];
int main()
{
    cin>>V>>N>>M;
    for(int i=1;i<=N;i++){
        cin>>v[i]>>c[i];
    }
    for(int i=1;i<=N;i++){
        for(int j=M;j>=c[i];j--){
            dp[j]=max(dp[j],dp[j-c[i]]+v[i]);
        }
    }
    for(int i=0;i<=M;i++){
        if(dp[i]>=V){
            cout<<M-i;
            return 0;
        }
    }
    cout<<"Impossible";


}
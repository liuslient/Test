#include<bits/stdc++.h>
using namespace std;

const int MN=5010;
int n,m,sb[MN],nb[MN],mp[MN][MN],mod=80112002,ans,r[MN];

int dfs(int x)
{
    if(!nb[x]){
        return 1;
    }
    if(r[x])
        return r[x];
    int sum=0;
    for(int i=1;i<=n;i++){
        if(mp[i][x]){
            sum=(sum+dfs(i))%mod;
        }
    }
    return r[x]=sum;
}

int main()
{
    cin>>n>>m;
    while (m--)
    {
        int x,y;
        cin>>x>>y;
        mp[x][y]=1;
        sb[x]++;
        nb[y]++;
    }
    for(int i=1;i<=n;i++){
        if(!sb[i]){
            ans=(ans+dfs(i))%mod;
        }
    }
    cout<<ans;
    
}
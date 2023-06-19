#include<bits/stdc++.h>
using namespace std;
int n,a[40],root[40][40];
long long dp[40][40];

long long dfs(int L,int R){
    if(L>R) return 1;
    if(dp[L][R]) return dp[L][R];
    long long maxn=0;
    for (int i = L; i <= R; i++)
    {
        long long t=dfs(L,i-1)*dfs(i+1,R)+a[i];
        if(t>maxn){
            maxn=t;
            root[L][R]=i;
        }
    }
    return dp[L][R]=maxn;
    
}

void dg(int L,int R){
    if(L>R) return ;
    printf("%d ",root[L][R]);
    dg(L,root[L][R]-1);
    dg(root[L][R]+1,R);
}

int main()
{
    //scanf("%d",&n);
    cin>>n;
    for (int i = 1; i <= n; i++)
    {
        cin>>a[i];
        dp[i][i]=a[i];
        root[i][i]=i;
    }
    printf("%lld\n",dfs(1,n));
    dg(1,n);
    
}
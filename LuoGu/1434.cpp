#include<bits/stdc++.h>
using namespace std;

int r,c,ans,a[110][110],dp[110][110];
int xx[]={0,1,0,-1};
int yy[]={1,0,-1,0};
int dfs(int x,int y)
{
    int maxn=1;
    if(dp[x][y]>0){
        return dp[x][y];
    }
    for (int i = 0; i < 4; i++)
    {
        int dx=xx[i]+x;
        int dy=yy[i]+y;
        if(a[dx][dy]<a[x][y]&&dx>=1&&dx<=r&&dy>=1&&dy<=c){
            maxn=max(maxn,dfs(dx,dy)+1);

        }
    }
    return dp[x][y]=maxn;
    
}

int main()
{
    cin>>r>>c;
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            cin>>a[i][j];
        }
        
    }
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            ans=max(ans,dfs(i,j));
        }
        
    }
    cout<<ans;
}
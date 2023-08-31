#include<bits/stdc++.h>
using namespace std;

int n,sum,y[20][20],vis[20],a[20],flag;
void dfs(int p,int s)
{
    if(flag){
        return;
    }
    if(p>n){
        if(s==sum){
            for (int i = 1; i <= n; i++)
            {
                cout<<a[i]<<" ";
            }
            flag=1;;
        }
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        if(!vis[i])
        {
            a[p]=i;
            vis[i]=1;
            if(s+y[n][p]*i<=sum)
                dfs(p+1,s+y[n][p]*i);
            vis[i]=0;
        }
    }
    
}
int main()
{
    cin>>n>>sum;
    y[1][1]=1;
    for (int i = 2; i <= 13; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            y[i][j]=y[i-1][j-1]+y[i-1][j];
        }
        
    }
    dfs(1,0);
    
    
    
    
}
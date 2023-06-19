#include<bits/stdc++.h>
using namespace std;
int n,ans;
string a[22];
int vis[22];
void dfs(string x,int s){
    ans=max(ans,s);
    for (int i = 1; i <= n; i++)
    {
        int p=1;
        int la=x.length();
        int lb=a[i].length();
        while (p<min(la,lb))
        {
            if(x.substr(la-p)==a[i].substr(0,p)&&vis[i]<2){
                vis[i]++;
                dfs(a[i],s+lb-p);
                vis[i]--;
                break;
            }
            p++;
        }
        
    }
    
}

int main()
{
    cin>>n;
    for (int i = 1; i <= n; i++)
    {
        cin>>a[i];
    }
    char t;
    cin>>t;
    for (int i = 1; i <= n; i++)
    {
        if(a[i][0]==t){
            vis[i]++;
            dfs(a[i],a[i].length());
            vis[i]--;
        } 
    }
    cout<<ans;
    
    
}
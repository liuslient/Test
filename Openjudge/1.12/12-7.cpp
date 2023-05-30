#include<bits/stdc++.h>
using namespace std;

int q[1005],hh=0,tt=-1;
bool st[1005];
int main()
{
    int m,n,ans=0;
    cin>>m>>n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin>>x;
        if(hh>tt){
            q[++tt]=x;
            st[x]=1;
            ans++;
        }else if(st[x]) continue;
        else if(tt-hh+1>=m){
            st[q[hh]]=0;
            hh++;
            ans++;
            q[++tt]=x;
            st[x]=1;
        }else if(tt-hh+1<m){
            ans++;
            q[++tt]=x;
            st[x]=1;
        }
    }
    cout<<ans;
    
}
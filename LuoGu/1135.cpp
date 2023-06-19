#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,a,b,e[210],vis[210];
    memset(vis,0,sizeof(vis));
    cin>>n>>a>>b;
    for (int i = 1; i <= n; i++)
    {
        cin>>e[i];
    }
    queue <int> f;
    queue <int> s;
    f.push(a);
    s.push(0);
    vis[a]=1;
    while (!f.empty())
    {
        if(f.front()==b){
            cout<<s.front();
            return 0;
        }
        int t=f.front()+e[f.front()];
        if(t<=n&&!vis[t]){
            f.push(t);
            s.push(s.front()+1);
            vis[t]=1;
        }
        t=f.front()-e[f.front()];
        if(t>=1&&!vis[t]){
            f.push(t);
            s.push(s.front()+1);
            vis[t]=1;
        }
        f.pop();
        s.pop();
    }
    cout<<-1;
    
    

}

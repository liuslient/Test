#include <iostream>
#include <queue>
using namespace std;
int xx[]={0,-1,0,1};
int yy[]={1,0,-1,0};
int mp[40][40];
bool vis[40][40];
int n,m;
int main()
{
    cin>>n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin>>mp[i][j];
        }
    }
    queue<int > x;
    queue<int> y;
    x.push(0);
    y.push(0);
    vis[0][0]=1;
    while (!x.empty())
    {
        
        for (int i = 0; i < 4; i++)
        {
            int dx=x.front()+xx[i];
            int dy=y.front()+yy[i];
            if(dx>=0&&dx<=n+1&&dy>=0&&dy<=n+1&&mp[dx][dy]==0&&!vis[dx][dy]){
                x.push(dx);
                y.push(dy);
                vis[dx][dy]=1;
            }
        }
        x.pop();
        y.pop();
        
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if(mp[i][j]==0&&vis[i][j]==0){
                cout<<2<<" ";
            }else{
                cout<<mp[i][j]<<" ";
            }
        }
        cout<<endl;
        
    }
    
    
}


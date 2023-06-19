#include<bits/stdc++.h>

using namespace std;
const int Maxn=55;
int n,m,sx,sy,tx,ty;
bool mp[Maxn][Maxn];
bool vis[Maxn][Maxn][4];
int xx[]={-1,0,1,0};
int yy[]={0,1,0,-1};
struct R
{
    int x,y,s,d;
};

int main()
{
    cin>>n>>m;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            int t;
            cin>>t;
            if(t){
                mp[i][j]=mp[i-1][j]=mp[i][j-1]=mp[i-1][j-1]=1;
            }
        }
    }
    queue <R> Q;
    char tt;
    cin>>sx>>sy>>tx>>ty>>tt;
    R t1;
    t1.x=sx;
    t1.y=sy;
    t1.s=0;
    if(tt=='N') t1.d=0;
    if(tt=='E') t1.d=1;
    if(tt=='S') t1.d=2;
    if(tt=='W') t1.d=3;
    Q.push(t1);
    while (!Q.empty())
    {
        t1=Q.front();
        vis[t1.x][t1.y][t1.d]=1;
        if(t1.x==tx&&t1.y==ty){
            cout<<t1.s;
            return 0;
        }
        R t=t1;
        t.s++;
        t.d=(t.d+1)%4;
        if(!vis[t.x][t.y][t.d]){
            Q.push(t);
        }
        t.d=(t.d+2)%4;
        if(!vis[t.x][t.y][t.d]){
            Q.push(t);
        }
        t.d=t1.d;
        t.x+=xx[t.d];
        t.y+=yy[t.d];
        if(t.x>=1&&t.x<n&&t.y>=1&&t.y<m&&!vis[t.x][t.y][t.d]&&!mp[t.x][t.y]){
            Q.push(t);
            t.x+=xx[t.d];
            t.y+=yy[t.d];
            if(!vis[t.x][t.y][t.d]&&!mp[t.x][t.y]){
                Q.push(t);
                t.x+=xx[t.d];
                t.y+=yy[t.d];
                if(!vis[t.x][t.y][t.d]&&!mp[t.x][t.y]){
                    Q.push(t);
                }
            }
        }
        Q.pop();
    }
    cout<<-1;
    

}

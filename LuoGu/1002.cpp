#include<bits/stdc++.h>
using namespace std;

int xx[9]={0,-2,-2,-1,-1,1,1,2,2};
int yy[9]={0,-1,1,-2,2,-2,2,-1,1};
long long f[30][30];
bool m[30][30];

int main()
{
    int c,r,ma,mb;
    cin>>c>>r>>ma>>mb;
    c++,r++,ma++,mb++;
    for (int i = 0; i < 9; i++)
    {
        int dx=ma+xx[i];
        int dy=mb+yy[i];
        m[dx][dy]=1;
    }
    f[1][1]=1;
    for(int i=1;i<=c;i++){
        for(int j=1;j<=r;j++){
            if(m[i][j]||i*j==1)
                continue;
            f[i][j]=f[i-1][j]+f[i][j-1];
        }
    }
    cout<<f[c][r];
    
}

#include <iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
using namespace std;
int n,p[30],a[30],mp[30][30],maxn,maxi;
int f[30];    //状态转移方程

void dg(int x)
{
    if(!x)
    {
        return;
    }
    dg(p[x]);
    cout<<x<<" ";
}

int main()
{
    int i,j;
    cin>>n;
    //地雷数
    for ( i = 1; i <= n; i++)
    {
        cin>>a[i];
        f[i]=a[i];
    }
    //路径关系
    for ( i = 1; i < n; i++)
    {
        for ( j = i+1; j <= n; j++)
        {
            cin>>mp[i][j];
        }
        
    }
    //动态规划
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j < i; j++)
        {
            if (mp[i][j])
            {
                if (f[i]<f[i]+a[i])
                {
                    f[i]=f[j]+a[i];
                    p[i]=j;
                }
            }
        }
        //求最大地雷
        if (maxn<f[i])
        {
            maxn=f[i];
            maxi=i;
        }
    }
    dg(maxi);
    cout<<endl<<maxn;

}
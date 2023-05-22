#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
    int n,m,i,j;
    cin>>n>>m;
    int a[n+10][m+10],b[n+10][m+10];
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= m; j++)
        {
            cin>>a[i][j];
            b[i][j]=a[i][j];
        }
        
    }
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= m; j++)
        {
            if (i==1||i==n||j==1||j==m)
            {
                continue;
            }
            else
            {
                b[i][j]=round((a[i][j]+a[i][j-1]+a[i][j+1]+a[i-1][j]+a[i+1][j])/5.0);
            }
            
        }
        
    }
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= m; j++)
        {
            cout<<b[i][j]<<" ";
        }
        cout<<endl;
        
    }
    
}
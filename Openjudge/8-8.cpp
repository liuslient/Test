#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
    int i,n,m,j;
    cin>>n>>m;
    int a[n+10][m+10],b[n+10][m+10];
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= m; j++)
        {
            cin>>a[i][j];
        }
        
    }
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= m; j++)
        {
            cin>>b[i][j];
        }
        
    }
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= m; j++)
        {
            a[i][j]+=b[i][j];
        }
        
    }
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= m; j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
        
    }
    
    
}
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
    int i,n,m,k,j,x,l;
    cin>>n>>m>>k;
    int a[n+10][m+10],b[m+10][k+10];
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= m; j++)
        {
            cin>>a[i][j];
        }
        
    }
    for ( i = 1; i <= m; i++)
    {
        for ( j = 1; j <= k; j++)
        {
            cin>>b[i][j];
        }
        
    }
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= k; j++)
        {
            x=0;
            for ( l = 1; l <= m; l++)
            {
                x+=a[i][l]*b[l][j];
                
            }
            cout<<x<<" ";
        }
        cout<<endl;
        
    }
    
    
}
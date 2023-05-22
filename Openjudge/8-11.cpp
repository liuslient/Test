#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
    int i,n,m,j;
    cin>>n>>m;
    int a[n+10][m+10];
    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < m; j++)
        {
            cin>>a[i][j];
        }
        
    }
    for ( i = 0; i < m; i++)
    {
        for ( j = 0; j < n; j++)
        {
            cout<<a[n-1-j][i]<<" ";
        }
        cout<<endl;
        
    }
    
    
}
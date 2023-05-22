#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>

using namespace std;
int a[1001][1001];

int main() {
    int n,m;
    cin>>n;
    m=n;
    for ( int i = 1; i <= n; i++)
    {
        for ( int j = 1; j <= n; j++)
        {
            cin>>a[i][j];
        }
        
    }
    for ( int i = 1; i <= n; i++)
    {
        cout<<a[2][2]<<endl;
        for ( int i = 1; i <= m; i++)
        {
            int x=1e9;
            for (int  j = 1; j <= m; j++)
            {
                x=min(x,a[i][j]);
            }
            for (int  j = 1; j <= m; j++)
            {
                a[i][j]-=x;
            }
            
            
        }
        for ( int i = 1; i <= m; i++)
        {
            int x=1e9;
            for (int  j = 1; j <= m; j++)
            {
                x=min(x,a[j][i]);
            }
            for (int  j = 1; j <= m; j++)
            {
                a[j][i]-=x;
            }
            
            
        }
        for (int i = 2; i <= m-1; i++)
        for (int j = 1; j <= m; j++)
        {
            a[i][j]=a[i+1][j];
        }
        for (int j = 2; j <= m; j++)
        for (int i = 1; i <= m-1; i++)
        {
            a[i][j]=a[i][j+1];
        }
        m--;
        
    }
    
    
    
}
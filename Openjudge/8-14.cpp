#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
    int n,m,i,j,flag=0;
    cin>>n>>m;
    char a[n+10][m+10],b[n+10][m+10];
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
            if (a[i][j]=='*')
            {
                b[i][j]='*';
            }
            else
            {
                flag=0;
                for (int ii = i-1; ii <= i+1; ii++)
                {
                    for (int jj = j-1; jj <= j+1; jj++)
                    {
                        if(a[ii][jj]=='*')
                        {
                            flag++;
                            
                        }
                    }
                    
                }
                b[i][j]=flag+'0';
            }
        }
    }
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= m; j++)
        {
            cout<<b[i][j];
        }
        cout<<endl;
    }

    
}
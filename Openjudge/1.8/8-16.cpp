#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
char win(char ch)
{
    if (ch == 'R') return 'P';
    if (ch == 'S') return 'R';
    return 'S';
}

int main()
{
    int n,r,c,i,j,flag=0;
    cin>>r>>c>>n;
    char a[r+10][c+10]={0},b[r+10][c+10]={0},ch;
    for ( i = 1; i <= r; i++)
    {
        for ( j = 1; j <= c; j++)
        {
            cin>>a[i][j];
        }
    }

    for (int day = 1; day <= n; day++)
    {
        for ( i = 1; i <= r; i++)
        {
            for ( j = 1; j <= c; j++)
            {
                ch=win(a[i][j]);
                if (a[i][j-1]==ch||a[i-1][j]==ch||a[i][j+1]==ch||a[i+1][j]==ch)
                {
                    b[i][j]=ch;
                }
                else
                {
                    b[i][j]=a[i][j];
                }
                
            }
            
        }
        for ( i = 1; i <= r; i++)
        {
            for ( j = 1; j <= c; j++)
            {
                a[i][j]=b[i][j];
                
            }
            
        }

        
    }
    
    
    for ( i = 1; i <= r; i++)
    {
        for ( j = 1; j <= c; j++)
        {
            cout<<a[i][j];
        }
        cout<<endl;
    }

    
}
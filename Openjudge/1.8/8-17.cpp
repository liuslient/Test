#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;


int main()
{
    int n,r,c,i,j,flag=0;
    cin>>r>>c;
    char a[r+10][c+10]={0},b[r+10][c+10]={0},ch;
    for ( i = 1; i <= r; i++)
    {
        for ( j = 1; j <= c; j++)
        {
            cin>>a[i][j];
            if (a[i][j] == '#' && a[i][j + 1] != '#' && a[i][j - 1] != '#' && a[i + 1][j]  != '#' && a[i - 1][j] != '#') 
			{
                flag++;
            }
        }
    }
    cout<<flag;
    
}
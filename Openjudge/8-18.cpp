#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int a[10001][10001]={0};
int main()
{
    int n,hang,lie,i,j,flag=0,l_h=0,l_l=0;
    cin>>n; 
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= n; j++)
        {
            cin>>a[i][j];
            
        }
    }
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= n; j++)
        {
            if (a[i-1][j]==0&&a[i-1][j-1]==0&&a[i][j-1]==0&&i!=1&&j!=1)
            {
                //记录左上行列
                hang=i;
                lie=j;
            }
            
        }
        
    }
    for ( i = hang; i <= 9999; i++)
    {
        for ( j = lie; j <= 9999; j++)
        {
            if (a[i][j]!=0)
            {
                l_l++;
            }
            else break;
            
        }
        break;
    }
    for ( i = hang; i <= 9999; i++)
    {
        if (a[i][lie]!=0)
        {
            l_h++;
        }
        else break;
        
    }
    cout<<l_h*l_l;
    
    
}
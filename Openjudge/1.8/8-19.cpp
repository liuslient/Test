#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int a[10001][10001]={0};
int main()
{
    int n,hang,lie,i,j,flag=0,cnt=0;
    cin>>n; 
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= n; j++)
        {
            cin>>a[i][j];
            if (a[i][j]<=50)
            {
                flag++;
            }
            
        }
    }
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= n; j++)
        {
            if (a[i][j]<=50)
            {
                if(a[i-1][j]<=50&&a[i+1][j]<=50&&a[i][j-1]<=50&&a[i][j+1]<=50&&i!=1&&j!=1&&i!=n&&j!=n)
                {
                    cnt++;
                }
            }
            
        }
    }
    cout<<flag<<" "<<flag-cnt;
    
    
}
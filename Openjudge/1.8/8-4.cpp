#include<iostream>
#include<string>
using namespace std;
int main()
{
    int n,i,j;
    cin>>n;
    int a[n+10][n+10];
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j<=n; j++)
        {
            cin>>a[i][j];
        }
    }
    int r[n+10]={0},c[n+10]={0};
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j<=n; j++)
        {
            r[i]+=a[i][j];
        }
    }
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j<=n; j++)
        {
            c[i]+=a[j][i];
        }
    }
    int sumr=0,sumc=0;
    for ( i = 1; i <= n; i++)
    {
        if(r[i]%2==1)
        {
            sumr++;
        }
    }
    for ( i = 1; i <= n; i++)
    {
        if(c[i]%2==1)
        {
            sumc++;
        }
    }
    if (sumr==0&&sumc==0)
    {
        cout<<"OK";
    }
    else if(sumr==1&&sumc==1)
    {
        for ( i = 1; i <= n; i++)
        {
            if (r[i]%2==1)
            {
                cout<<i<<" ";
            }
        }
        for ( i = 1; i <= n; i++)
        {
            if (c[i]%2==1)
            {
                cout<<i<<" ";
            }
        }
    }
    else
    {
        cout<<"Corrupt";
    }
    

}
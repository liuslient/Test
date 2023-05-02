#include <iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
using namespace std;
int main()
{
    int i,j,n=0,ans=0;
    string a[120],t;
    while (cin>>a[++n]);
    for ( i = 1; i < n; i++)
    {
        for ( j = 1; j <= n-i;j++)
        {
            if (a[j]>a[j+1])
            {
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
    for ( i = 1; i <= n; i++)
    {
        if(a[i]!=a[i-1])
        { 
            cout<<a[i]<<endl;
        }
    }
    
}
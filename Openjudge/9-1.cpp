#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int main()
{
    int n,x,i;
    cin>>n;
    int a[n+10];
    for ( i = 1; i <= n; i++)
    {
        cin>>a[i];
    }
    cin>>x;
    for ( i = 1; i <= n; i++)
    {
        if (a[i]==x)
        {
            cout<<i;
            return 0;
        }
        
    }
    cout<<-1;
    
    
}
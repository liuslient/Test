#include<iostream>
#include<cstring>
#include<string>
using namespace std;
int main()
{
    int n,i,max,sum=0;
    cin>>n;
    int a[n+10];
    for ( i = 1; i <= n; i++)
    {
        cin>>a[i];
    }
    max=a[1];
    for ( i = 1; i <= n; i++)
    {
        if (max<=a[i])
        {
            max=a[i];
        }
    }
    for ( i = 1; i <= n; i++)
    {
        if (max==a[i])
        {
            a[i]=0;
        }
    }
    for ( i = 1; i <= n; i++)
    {
        sum+=a[i];
    }
    cout<<sum;
    
    
}

#include <iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
using namespace std;
int main()
{
    int n,i,j,ans=1;
    cin>>n;
    int a[n+10];
    for ( i = 1; i <= n; i++)
    {
        cin>>a[i];
    }
    for ( i = 1; i < n; i++)
    {
        for ( j = 1; j <= n-i;j++)
        {
            if (a[j]>a[j+1])
            {
                swap(a[j],a[j+1]);
            }
        }
    }
    for ( i = 2; i <= n; i++)
    {
        if(a[i]==a[i-1])
            continue;
        else
            ans++;
    }
    cout<<ans<<endl;
    cout<<a[1]<<" ";
    for ( i = 2; i <= n; i++)
    {
        if (a[i]==a[i-1])
        {
            continue;
        }
        else
            cout<<a[i]<<" ";
        
    }
}
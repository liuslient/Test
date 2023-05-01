#include <iostream>
#include<iomanip>
#include<cmath>
using namespace std;
int main()
{
    int i,j,n,k;
    cin>>n;
    string b[n+10],t;
    int a[n+10];
    for ( i = 1; i <= n; i++)
    {
        cin>>b[i]>>a[i];
    }
    
    for ( i = 1; i < n; i++)
    {
        for ( j = 1; j<=n-i; j++)
        {
            if (a[j]<a[j+1])
            {
                swap(a[j],a[j+1]);
                t=b[j];
                b[j]=b[j+1];
                b[j+1]=t;
            }
            if (a[j]==a[j+1] && b[j]>b[j+1])
            {
                swap(a[j],a[j+1]);
                t=b[j];
                b[j]=b[j+1];
                b[j+1]=t;
            }
            
        }
    }
    for ( i = 1; i <= n; i++)
    {
        cout<<b[i]<<" "<<a[i]<<endl;
    }
}
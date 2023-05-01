#include <iostream>
#include<iomanip>
#include<cmath>
using namespace std;
int main()
{
    int i,j,n,k;
    cin>>n>>k;
    int b[n+10];
    double a[n+10];
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
                swap(b[j],b[j+1]);
            }
            
        }
    }
    cout<<b[k]<<" "<<a[k];
}
#include <iostream>
#include<iomanip>
#include<cmath>
using namespace std;
int main()
{
    int i,j=0,n;
    cin>>n;
    int a[n+10],b[n+10];
    for ( i = 1; i <= n; i++)
    {
        cin>>a[i];
        
    }
    for ( i = 1; i < n; i++)
    {
        for ( j = 1; j<=n-i; j++)
        {
            if (a[j]>a[j+1])
            {
                swap(a[j],a[j+1]);
            }
        }
    }
    
    
    int flag=1;
    for ( i = 1; i <= n; i++)
    {
        if (a[i]%2!=0)
        {
            if (flag==1)
            {
                cout<<a[i];
                flag=0;
            }
            else
            {
                cout<<","<<a[i];
            }
            
        }
        
        
    }

}
#include <iostream>
#include<iomanip>
#include<cmath>
using namespace std;
int main()
{
    int i,j,n,m,k;
    int a[10];
    for ( i = 0; i < 10; i++)
    {
        cin>>a[i];
    }
    for ( i = 0; i < 9; i++)
    {
        for ( j = 0; j < 9-i;j++)
        {
            if (a[j]%2==0&&a[j+1]%2==1 || a[j]%2==1&&a[j+1]%2==1&&a[j]<a[j+1] || a[j]%2==0&&a[j+1]%2==0&&a[j]>a[j+1])
            {
                swap(a[j],a[j+1]);
            }
            
        }
        
    }
    for ( i = 0; i < 10; i++)
    {
        cout<<a[i]<<" ";
    }
    
    
    
}
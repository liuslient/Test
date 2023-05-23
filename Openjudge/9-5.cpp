#include<iostream>
#include<cstring>
#include<string>
using namespace std;
int main()
{
    int m,i,min,max;
    cin>>m;
    int a[m+10];
    for ( i = 1; i <= m; i++)
    {
        cin>>a[i];
    }
    min=a[1];
    max=a[1];
    for ( i = 1; i <= m; i++)
    {
        if (min>=a[i])
        {
            min=a[i];
        }
        if (max<=a[i])
        {
            max=a[i];
        }
        
        
    }
    cout<<max-min;

    
}

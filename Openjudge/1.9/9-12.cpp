#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;

int main()
{
    int n,i,j,len=0,len_max=0;
    cin>>n;
    int a[n+10],b[n+10];
    for ( i = 0; i < n; i++)
    {
        cin>>a[i];
    }
    for ( i = 0; i < n; i++)
    {
        len=0;
        for ( j = i+1; j < n; j++)
        {
            if (a[i]==a[j])
            {
                len++;
            }
            
        }
        if (len>=len_max)
        {
            len_max=len+1;
        }
        
        
        
    }
    cout<<len_max;
    
    
}
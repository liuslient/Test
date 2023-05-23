#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int main()
{
    int n,x,i,max=-1;
    cin>>n;
    int a[n+10];
    string s[n+10];
    for ( i = 1; i <= n; i++)
    {
        cin>>a[i]>>s[i];
        if (a[i]>=max)
        {
            max=a[i];
        }
        
    }
    for ( i = 1; i <= n; i++)
    {
        if (a[i]==max)
        {
            cout<<s[i];
            return 0;
        }
        
    }
    
    
    
}
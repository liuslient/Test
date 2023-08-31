#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[1000]={1};
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            a[i]+=a[j]*a[i-1-j];
            a[i]%=100;
        }
        
    }
    cout<<a[n];
    
}
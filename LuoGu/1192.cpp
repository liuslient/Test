#include<bits/stdc++.h>
using namespace std;
int a[100005]={1},n,k;
int main()
{
    cin>>n>>k;
    for (int i = 1; i < k; i++)
    {
        for (int j = 0; j < i; j++)
        {
            a[i]+=a[j];
            a[i]%=100003;
        }
        
    }
    for (int i = k; i <= n; i++)
    {
        for (int j = i-k; j < i; j++)
        {
            a[i]+=a[j];
            a[i]%=100003;
        }
        
    }
    cout<<a[n];
    
    
}
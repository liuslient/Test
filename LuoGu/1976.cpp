#include<bits/stdc++.h>
using namespace std;
long long a[3333]={1};
int main()
{
    int n;
    cin>>n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            a[i]+=a[j]*a[i-1-j];
            a[i]%=100000007;
        }
        
    }
    cout<<a[n];
    
}
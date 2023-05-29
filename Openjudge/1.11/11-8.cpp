#include<bits/stdc++.h>
using namespace std;
int m,n,a[1000005];


int main()
{
    cin>>n;
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }
    sort(a,a+n);
    cout<<a[0]<<" ";
    int last=a[0];
    for (int i = 1; i < n; i++)
    {
        int pos=upper_bound(a+1,a+n,last)-a;
        if(pos<n) {
            cout<<a[pos]<<" ";
            last=a[pos];
        }
        i=pos;
    }
    
    
}
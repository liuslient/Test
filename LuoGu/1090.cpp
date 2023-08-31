#include<bits/stdc++.h>
using namespace std;
int n,a[100010],p=1,s;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    for(int i=1;i<n;i++){
        a[p+1]+=a[p];
        s+=a[p+1];
        p++;
        sort(a+p,a+n+1);
    }
    cout<<s;
}
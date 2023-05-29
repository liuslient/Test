#include<bits/stdc++.h>
using namespace std;

int s,m,n,a[1000001];
bool check(int x)
{
    int res=0,now=0;
    for (int i = 1; i <= n+1; i++)
    {
        if(a[i]-now<x) res++;
        else {
            now=a[i];
        }
    }
    return res<=m;
    
}

int main()
{
    cin>>s>>n>>m;
    for (int i = 1; i <= n; i++)
    {
        cin>>a[i];
    }
    a[n+1]=s;
    int L=1,R=s;
    while(L<R){
        int mid=(L+R+1)/2;
        if(check(mid)) L=mid;
        else R=mid-1;
    }
    cout<<L;
    
}
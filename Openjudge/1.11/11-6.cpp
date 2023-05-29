#include<bits/stdc++.h>
using namespace std;
int m,n,a[1000005];
bool check(int x){
    int res=1,sum=0;
    for (int i = 0; i < n; i++)
    {
        if(a[i]+sum<=x){
            sum+=a[i];
        }else{
            sum=a[i];
            res++;
        }
    }
    return res<=m;
    
}

int main()
{
    cin>>n>>m;
    int L=0,R=0;
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
        L=max(a[i],L);
        R+=a[i];
    }
    while(L<R){
        int mid=(L+R)/2;
        if(check(mid)) R=mid;
        else L=mid+1;
    }
    cout<<L;
    
}
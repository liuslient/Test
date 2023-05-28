#include<bits/stdc++.h>

using namespace std;
long long r,n;
struct Rectangle
{
    long long l,t,w,h;
} a[1000005];

long long calc(long long x){
    long long sl=0,sr=0;
    for(int i=0;i<n;i++){
        if(a[i].l>=x){
            sr+=a[i].w*a[i].h;
        }else if(a[i].l+a[i].w<=x){
            sl+=a[i].w*a[i].h;
        }else{
            sr+=(a[i].l+a[i].w-x)*a[i].h;
            sl+=(x-a[i].l)*a[i].h;
        }
    }
    return sl-sr;
}

int main()
{

    cin>>r>>n;
    for (int i = 0; i < n; i++)
    {
        cin>>a[i].l>>a[i].t>>a[i].w>>a[i].h;
    }
    long long L=0,R=r;
    while(L<R){
        long long mid=(L+R)/2;
        if(calc(mid)>=0) R=mid;
        else L=mid+1;
    }
    long long d=calc(L);
    while(L<r&&calc(L+1)==d) L++;
    cout<<L;
}
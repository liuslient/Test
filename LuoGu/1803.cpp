#include<bits/stdc++.h>
using namespace std;
int n,cnt,cur;
struct yyy
{
    int s,t;
}a[1000100];
bool cmp(yyy x,yyy y){
    return x.t<y.t;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%d %d",&a[i].s,&a[i].t);
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        if(a[i].s>=cur){
            cur=a[i].t;
            cnt++;
        }
    }
    cout<<cnt;
}

#include<bits/stdc++.h>
using namespace std;
const int Mn=50005;
struct bag
{
    int tot;
    int w[Mn];
    int v[Mn]; 
}a[1000];
int dp[Mn];
int main()
{
    int n,m;
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        int x,y,z;
        cin>>x>>y>>z;
        if(z==0){
            a[i].tot=1;
            a[i].w[1]=x;
            a[i].v[1]=x*y;
        }else{
            if(a[z].tot==1){
                a[z].tot=2;
                a[z].w[2]=a[z].w[1]+x;
                a[z].v[2]=a[z].v[1]+x*y;
            }else{
                a[z].w[3]=a[z].w[1]+x;
                a[z].v[3]=a[z].v[1]+x*y;
                a[z].w[4]=a[z].w[2]+x;
                a[z].v[4]=a[z].v[2]+x*y;
                a[z].tot=4;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=m;j>=0;j--){
            for(int k=1;k<=a[i].tot;k++){
                if(j-a[i].w[k]>=0)
                    dp[j]=max(dp[j],dp[j-a[i].w[k]]+a[i].v[k]);
            }
        }
    }
    cout<<dp[m];
}
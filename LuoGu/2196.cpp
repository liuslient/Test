#include<bits/stdc++.h>
using namespace std;

int n,p[30],a[30],mp[30][30],maxn,maxi;
int f[30];

void dg(int x)
{
    if(!x)
        return;
    dg(p[x]);
    cout<<x<<" ";
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        f[i]=a[i];
    }
    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++){
            cin>>mp[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            if(mp[j][i])
                if(f[i]<f[j]+a[i]){
                    f[i]=f[j]+a[i];
                    p[i]=j;
                }
        }
        if(maxn<f[i]){
            maxn=f[i];
            maxi=i;
        }
    }
    dg(maxi);
    cout<<endl<<maxn;
}
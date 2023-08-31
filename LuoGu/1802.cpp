#include<bits/stdc++.h>
using namespace std;

int n,x,win[1010],use[1010],lose[1010];
long long f[1010];

int main()
{
    cin>>n>>x;
    for(int i=1;i<=n;i++){
        cin>>lose[i]>>win[i]>>use[i];
    }
    for (int i = 1; i <=n ; i++){
        for(int j=x;j>=0;j--){
            if(j>=use[i]){
                f[j]=max(f[j]+lose[i],f[j-use[i]]+win[i]);
            }else{
                f[j]=f[j]+lose[i];
            }
        }
    }
    cout<<f[x]*5;
}
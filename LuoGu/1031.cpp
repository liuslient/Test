#include<bits/stdc++.h>
using namespace std;
int n,a[110],sum,cnt;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum+=a[i];
    }
    sum/=n;
    for(int i=1;i<n;i++){
        if(a[i]!=sum){
            a[i+1]-=sum-a[i];
            cnt++;
        }
    }
    cout<<cnt;
}
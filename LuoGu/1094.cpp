#include<bits/stdc++.h>
using namespace std;
const int Mn=50005;
int L=1,cnt;
int n,w,a[Mn];
int main()
{
    cin>>w>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    while(L<=n){
        if(a[n]+a[L]<=w){
            cnt++;
            L++;
            n--;
        }else{
            n--;
            cnt++;
        }
    }
    cout<<cnt;
}
#include<bits/stdc++.h>
using namespace std;
const int Mn=50005;

int main()
{
    int n,m,a,cnt=1,s=0;
    cin>>n>>m;
    while(n--){
        cin>>a;
        if(s+a<=m){
            s+=a;
        }else{
            cnt++;
            s=a;
        }
    }
    cout<<cnt;

}
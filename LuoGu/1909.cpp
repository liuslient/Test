#include<iostream>
using namespace std;
int main()
{
    int x,y,p,ans=1e9,t;
    cin>>p;
    cin>>x>>y;
    if(p%x==0){
        t=p/x*y;
    }else{
        t=(p/x+1)*y;
    }
    if(ans>t){
        ans=t;
    }
    cin>>x>>y;
    if(p%x==0){
        t=p/x*y;
    }else{
        t=(p/x+1)*y;
    }
    if(ans>t){
        ans=t;
    }
    cin>>x>>y;
    if(p%x==0){
        t=p/x*y;
    }else{
        t=(p/x+1)*y;
    }
    if(ans>t){
        ans=t;
    }
    cout<<ans;
}


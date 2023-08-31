#include<bits/stdc++.h>
using namespace std;
int n,a,b,ls=1;
long long s[4005],ans[4005],lans;
struct dc{
    int x,y;
}c[1010];

bool cmp(dc e,dc f){
    return e.x*e.y<f.x*f.y;
}

void f(int t){
    int d[4005]={0},ld=ls;
    for(int i=ls;i>=1;i--){
        d[i]+=s[i];
        d[i-1]+=d[i]%t*10;
        d[i]/=t;
    }
    while(d[ld]==0&&ld>1){
        ld--;
    }
    int flag=0;
    if(lans<ld){
        flag=1;
    }
    else if(lans>ld){
        flag=0;
    }
    else{
        for(int i=ld;i>=1;i--){
            if(ans[i]>d[i]){
                flag=0;
                break;
            }
            if(ans[i]<d[i]){
                flag=1;
                break;
            }
        }
    }
    if(flag){
        lans=ld;
        for(int i=1;i<=ld;i++){
            ans[i]=d[i];
        }
    }
}

int main()
{
    cin>>n>>s[1]>>b;
    for(int i=1;i<=n;i++){
        cin>>c[i].x>>c[i].y;
    }
    sort(c+1,c+n+1,cmp);
    for(int i=1;i<=n;i++){
        f(c[i].y);
        for(int j=1;i<=ls;j++){
            s[j]*=c[i].x;
        }
        for(int j=1;i<=ls;j++){
            s[j+1]+=s[j]/10;
            s[j]%=10;
            if(s[ls+1]>0){
                ls++;
            }
        }
        
    }
    for(int i=lans;i>=1;i--){
        cout<<ans[i];
    }
}
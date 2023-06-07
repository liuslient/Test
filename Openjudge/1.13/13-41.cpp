#include<bits/stdc++.h>
using namespace std;
int  a,b,c;
bool f(int k,int x)
{
    if(k>x||k>100000){
        return 0;
    }if(k==x){
        return 1;
    }else{
        return(f(2*k+1,x)||f(3*k+1,x));
    }
}
int main()
{
    scanf("%d,%d",&a,&b);
    c=f(a,b);
    if(c==1){
        cout<<"YES";
    }else{
        cout<<"NO";
    }
}
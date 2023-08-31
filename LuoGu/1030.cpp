#include<bits/stdc++.h>
using namespace std;
char a[10],b[10];

void f(int x,int y,int z)
{
    if(z==0){
        return;
    }
    cout<<b[y+z-1];
    int len;
    for(int i=x;i<x+z;i++){
        if(a[i]==b[y+z-1]){
            len=i-x;
            break;
        }
    }
    f(x,y,len);
    f(x+len+1,y+len,z-1-len);
}

int main()
{
    cin>>a>>b;
    f(0,0,strlen(a));
}
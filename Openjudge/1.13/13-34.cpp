#include <bits/stdc++.h>
using namespace std;

int maxnum(int a)
{
    int num[7];
    int i=0;
    int ans;
    while (a)
    {
        num[i++]=a%10;
        a/=10;
    }
    sort(num,num+i);
    ans=num[i-1];
    return ans;
}

int zhuan(int a,int d)
{
    int ans=0;
    int num[7];
    int temp=a;
    int i=0;
    while (temp)
    {
        num[i++]=temp%10;
        temp/=10;
    }
    int z=1;
    for (int j = 0; j < i; j++)
    {
        ans+=num[j]*z;
        z*=d;
    }
    return ans;
}

int main()
{
    int p,q,r;
    cin>>p>>q>>r;
    int  jud=max(maxnum(p),maxnum(q));
    int number=max(jud,maxnum(r))+1;
    int flag=0;
    for (int i = number; i <= 16; i++)
    {
        if(zhuan(p,i)*zhuan(q,i)==zhuan(r,i)){
            cout<<i;
            return 0;
        }
    }
    cout<<0;
}












/*
int q,p,r;
int fun(int n,int d){
    int s=0,t=1;
    while (n!=0)
    {
        s=s+(n%10)*t;
        t=t*d;
        n=n/10;
    }
    return s;
    
}

int main()
{
    cin>>p>>q>>r;
    for (int i = 2; i <= 100; i++)
    {
        if(fun(p,i)*fun(q,i)==fun(r,i)){
            cout<<i;
            return 0;
        }
    }
    cout<<0;
}
*/
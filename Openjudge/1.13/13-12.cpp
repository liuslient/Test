#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int main()
{
    long long n,p=0,q=1,zi[10],mu[10],sum=0,t,i,g;
    cin>>n;
    for (int i = 0; i < n; i++)
    {
        scanf("%lld/%lld",&zi[i],&mu[i]);
        q*=mu[i];
    }
    if(n==1)
    {
        p=zi[0];
        q=mu[0];
        g=__gcd(p,q);
        p/=g;
        q/=g;
        if(q==1)
        {
            cout<<p;
        }
        else
        {
            printf("%lld/%lld",p,q);
        }
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        zi[i]*=q/mu[i];
        p+=zi[i];
    }
    g=__gcd(p,q);
    p/=g;
    q/=g;
    if(q==1)
    {
        cout<<p;
    }
    else
    {
        printf("%lld/%lld",p,q);
    }
    
    return 0;
}
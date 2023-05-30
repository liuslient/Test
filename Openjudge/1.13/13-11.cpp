#include<bits/stdc++.h>
using namespace std;
#define N 100005
int rev(int x)
{
    int num=0;
    for (int a = x; a > 0; a/=10)
    {
        num=num*10+a%10;
    }
    return num;
    
}
bool isPrime(int n)
{
    if(n<2)
        return false;
    for (int i = 2; i <= sqrt(n); i++)
    {
        if(n%i==0)
            return false;
    }
    return true;
    
}
int main()
{
    int n,d,x,y,num,mi,mx;
    int a[N],ai=0;
    cin>>n;
    if(n%2==0)
        d=n/2;
    else
        d=(n+1)/2;
    mi=pow(10,d-1);
    mx=10*mi;
    for ( x = mi; x < mx; ++x)
    {
        y=rev(x);
        if(n%2==0)
            num=x*mx+y;
        else
            num=x/10*mx+y;
        if(isPrime(num))
            a[++ai]=num;
    }
    cout<<ai<<endl;
    for (int i = 1; i <= ai; i++)
    {
        cout<<a[i]<<" ";
    }
    
    
}
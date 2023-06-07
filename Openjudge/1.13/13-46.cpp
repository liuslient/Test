#include <bits/stdc++.h>
using namespace std;
int main()
{
    long sum=0,a,x=1;
    cin>>a;
    while (a!=0)
    {
        sum=sum+a%10*x;
        x=x*8;
        a=a/10;
    }
    cout<<sum<<endl;
    
}

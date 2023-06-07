#include <bits/stdc++.h>
using namespace std;
int main()
{
    long sum=0,a,x=1;
    cin>>a;
    while (a!=0)
    {
        sum=sum+(a%8)*x;
        a=a/8;
        x=x*10;
    }
    cout<<sum<<endl;
    
}

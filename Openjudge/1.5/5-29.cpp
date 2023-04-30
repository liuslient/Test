#include<iostream>
using namespace std;

int main()
{
    int n,m=0;
    cin>>n;
    if (n<0)
    {
        cout<<"-";
        n=-n;
    }
    
    while (n>0)
    {
        m*=10;
        m+=n%10;
        n/=10;
    }
    cout<<m;
    
    
    
}
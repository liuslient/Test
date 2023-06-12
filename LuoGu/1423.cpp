#include<iostream>
using namespace std;
int main()
{
    double s=0,a=2.0,x;
    int cnt=0;
    cin>>x;
    while (s<x)
    {
        s+=a;
        a*=0.98;
        cnt++;
    }
    cout<<cnt;
    
    
    
    
}


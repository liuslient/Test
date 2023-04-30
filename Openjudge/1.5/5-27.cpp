#include<iostream>
using namespace std;

int main()
{
    int i=1,k,n;
    double sn=0;
    cin>>k;
    while(sn<=k)
    {
        sn+=1.0/i;
        i++;
    }
    cout<<i-1;
    
}
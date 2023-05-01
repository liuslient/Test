#include<iostream>
using namespace std;
int main()
{
    int n,c,i,sum=0,sta=0;
    cin>>n;
    for ( i = 1; i <= n; i++)
    {
        sta=0;
        if (i%7==0||i%10==7||i/10==7)
        {
            sta=1;
        }
        if (sta==0)
        {
            sum+=i*i;
        }
        
        
    }
    cout<<sum;
    
}
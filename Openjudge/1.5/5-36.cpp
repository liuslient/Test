#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

int main()
{
    int n,i,j;
    float sum=0,x;
    cin>>x>>n;
    for ( i = 0; i <= n; i++)
    {
        
        sum+=pow(x,i);
    }
    cout<<fixed<<setprecision(2)<<sum;
    
}
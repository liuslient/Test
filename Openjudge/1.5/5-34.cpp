#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

int main()
{
    int n,i,j;
    double e=0,cheng=1;
    cin>>n;
    for ( i = 1; i <= n; i++)
    {
        cheng =1;
        for ( j = 1; j <=i; j++)
        {
            cheng/=j;
        }
        e+=cheng;
        
    }
    cout<<fixed<<setprecision(10)<<e+1;
    
}
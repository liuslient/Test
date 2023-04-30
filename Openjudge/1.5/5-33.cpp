#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

int main()
{
    int n,i,j,sum=0,cheng=1;
    cin>>n;
    for ( i = 1; i <= n; i++)
    {
        cheng =1;
        for ( j = 1; j <=i; j++)
        {
            cheng*=j;
        }
        sum+=cheng;
        
    }
    cout<<sum;
    
}
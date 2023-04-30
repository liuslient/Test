#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int n,i,s;
    double sum=0,p,q;
    cin>>n;
    p=1;
    q=2;
    for ( i = 1; i <= n; i++)
    {
        sum+=q/p;
        s=q;
        q=q+p;
        p=s;
    }
    cout<<fixed<<setprecision(4)<<sum;
    
}
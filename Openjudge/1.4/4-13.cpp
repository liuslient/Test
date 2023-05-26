#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
    double n,y;
    cin>>n;
    if (n>=0&&n<5)
    {
        y=-1*n+2.5;
    }
    if (n>=5&&n<=10)
    {
        y=2-1.5*(n-3)*(n-3);
    }
    if (n>=10&&n<=20)
    {
        y=n/2.0-1.5;
    }
    
    cout<<fixed<<setprecision(3)<<y;
    
}
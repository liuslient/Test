#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
    int wei,cost=8;
    char s;
    cin>>wei>>s;
    if(s=='y')
    {
        cost+=5;
    }
    if (wei>1000)
    {
        wei -= 1000;
        cost += wei/500*4;
        if (wei%500 != 0) cost += 4;
    }
    cout<<cost;
    
    
}
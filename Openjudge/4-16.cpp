#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
    int a,b,c,i,j;
    cin>>a>>b>>c;
    if(a+b>c&&b+c>a&&a+c>b&&a-b<c&&b-c<a&&a-c<b)
    {
        cout<<"yes";
    }
    else
    {
        cout<<"no";
    }
    
}
#include<iostream>
using namespace std;

int main()
{
    int a;
    for(a=82;a<=342;a++)
    {
        if(a/81==a%7&&a/9%9==a/7%7&&a%9==a/49)
        {
            cout<<a<<endl;
            cout<<a/49<<a/7%7<<a%7<<endl;
            cout<<a/81<<a/9%9<<a%9<<endl;
        }
    }
}
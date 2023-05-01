#include<iostream>
#include<string>
using namespace std;
int main()
{
    string a;
    int i,n,la;
    cin>>a;
    la=a.length();
    if (a[la-1]=='r'&&a[la-2]=='e' || a[la-1]=='y'&&a[la-2]=='l')
    {
        la-=2;
    }
    if (a[la-1]=='g'&&a[la-2]=='n'&&a[la-3]=='i')
    {
        la-=3;
    }
    for ( i = 0; i < la; i++)
    {
        cout<<a[i];
    }
}
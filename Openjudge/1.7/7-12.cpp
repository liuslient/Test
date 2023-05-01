#include<iostream>
#include<string>
using namespace std;
int main()
{
    string a,b="";
    int i;
    cin>>a;
    for ( i = 0; i < a.length(); i++)
    {
        if (a[i]>='A'&&a[i]<='Z')
        {
            a[i]+=32;
        }
        else if (a[i]>='a'&&a[i]<='z')
        {
            a[i]-=32;
        }
    }
    for ( i = a.length()-1; i >= 0; i--)
    {
        b=b+a[i];
    }
    for ( i = 0; i < b.length(); i++)
    {
        b[i]+=3;
        if (b[i]>'z'||b[i]>'Z'&&b[i]<'a')
        b[i]-=26;
    }
    cout<<b;
    
    
    
    
}
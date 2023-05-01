#include<iostream>
#include<string>
using namespace std;
int main()
{
    string a,b;
    int i,n,j;
    getline(cin,a);
    getline(cin,b);
    for ( i = 0; i < a.length(); i++)
    {
        if (a[i]>='A'&&a[i]<='Z')
        {
            a[i]+=32;
        }
        
    }
    for ( i = 0; i < b.length(); i++)
    {
        if (b[i]>='A'&&b[i]<='Z')
        {
            b[i]+=32;
        }
        
    }
    if (a==b)
    {
        cout<<'=';
    }
    if (a>b)
    {
        cout<<'>';
    }
    if (a<b)
    {
        cout<<'<';
    }
    
    
    
}
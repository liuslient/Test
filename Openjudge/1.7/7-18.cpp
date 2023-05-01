#include<iostream>
#include<string>
using namespace std;
int main()
{
    string a,b,c="";
    int i,n,j;
    getline(cin,a);
    getline(cin,b);
    for ( i = 0; i < b.length(); i++)
    {
        c="";
        for ( j = 0; j < a.length(); j++)
        {
            c+=b[j+i];
        }
        if (a==c)
        {
            cout<<a<<" is substring of "<<b;
            return 0;
        } 
    }
    for ( i = 0; i < a.length(); i++)
    {
        c="";
        for ( j = 0; j < b.length(); j++)
        {
            c+=a[j+i];
        }
        if (b==c)
        {
            cout<<b<<" is substring of "<<a;
            return 0;
        } 
    }
    cout<<"No substring";
}
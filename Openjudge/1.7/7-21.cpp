#include<iostream>
#include<string>
using namespace std;
int main()
{
    string a,b,c,d="";
    int i,n,la;
    getline(cin,a);
    cin>>b>>c;
    a=a+' ';
    for ( i = 0; i < a.length(); i++)
    {
        d="";
        while (a[i]!=' ')
        {
            d+=a[i];
            i++;
        }
        if (d==b)
        {
            cout<<c;
        }
        else
        {
            cout<<d;
        }
        cout<<' ';
    }
    
}
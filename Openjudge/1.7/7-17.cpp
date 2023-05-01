#include<iostream>
#include<string>
using namespace std;
int main()
{
    string a,b,c="",d="";
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
    for ( i = 0; i < a.length(); i++)
    {
        if (a[i]>='a'&&a[i]<='z')
        {
            c+=a[i];
        }  
    }
    for ( i = 0; i < b.length(); i++)
    {
        if (b[i]>='a'&&b[i]<='z')
        {
            d+=b[i];
        } 
    }
    if (c==d)
    {
        cout<<"YES";
    }
    else
    {
        cout<<"NO";
    }
    

}
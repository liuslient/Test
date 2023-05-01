#include<iostream>
#include<string>
using namespace std;
int main()
{
    string a,b,c="";
    int i,n,j;
    cin>>a>>b;
    c=b+b;
    if(c.find(a)!=string::npos&&a.length()<=b.length())
    {
        cout<<"true";
        return 0;
    }
    c=a+a;
    if(c.find(b)!=string::npos&&a.length()>=b.length())
    {
        cout<<"true";
        return 0;
    }
    cout<<"false";
}
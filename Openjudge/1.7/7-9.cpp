#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s;
    char a,a_t;
    int i,n;
    getline(cin,s);
    for ( i = 0; i < s.length(); i++)
    {
        if (s[i]>='a'&&s[i]<='y'||s[i]>='A'&&s[i]<='Y')
        {
            cout<<char(s[i]+1);
        }
        else if (s[i]=='Z')
        {
            cout<<"A";
        }
        else if (s[i]=='z')
        {
            cout<<"a";
        }
        else
        {
            cout<<s[i];
        }
    }
}
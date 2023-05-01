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
        if (s[i]>='A'&&s[i]<='E')
        {
            cout<<char(s[i]-5+26);
        }
        else if (s[i]>='F'&&s[i]<='Z')
        {
            cout<<char(s[i]-5);
        }
        else
        {
            cout<<s[i];
        }
    }
}
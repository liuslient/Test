#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s;
    int i,n;
    getline(cin,s);
    for ( i = 0; i < s.length()-1; i++)
    {
        cout<<char(s[i]+s[i+1]);
    }
    cout<<char(s[0]+s[i]);
    

}
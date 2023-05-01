#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s,s2;
    int i,n;
    cin>>s;
    for ( i = 0; i < s.length(); i++)
    {
        if (s[i]=='A')
        {
             cout<<'T';
        }
        if(s[i]=='T')
        {
             cout<<'A';
        }

        if(s[i]=='G')
        {
             cout<<'C';
        }
        if(s[i]=='C')
        {
             cout<<'G';
        }
        
    }    
}
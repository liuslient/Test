#include<iostream>
#include<cstdio>
#include<cmath>
#include<string.h>
using namespace std;
int main()
{
    string s;
    int i,l;
    getline(cin,s);
    l=s.length();
    for ( i = 0; i < l; i++)
    {
        if (s[i]==' '&&s[i+1]==' ')
        {
            continue;
        }
        cout<<s[i];
        
    }
    
}
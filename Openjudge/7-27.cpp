#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
    string s;
    int i,l,z=0,j;
    getline(cin,s);
    s=s+' ';
    l=s.length();
    for ( i = 0; i <= l+2; i++)
    {
        if (s[i]==' ')
        {
            for (j = i-1; j >= z; j--)
            {
                cout<<s[j];
            }
            cout<<" ";
            z=i+1; 
        }    
    }
    return 0;
}

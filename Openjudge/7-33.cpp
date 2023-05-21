#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int main()
{
    string s1,s2;
    cin>>s1;
    int l,i;
    l=s1.length();
    for ( i = 0; i < l; i++)
    {
        if (s1[i]!=s1[l-i-1])
        {
            cout<<"no";
            return 0;
        }
        
    }
    cout<<"yes";
    
    
    
}
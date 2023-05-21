#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int main()
{
    string s;
    cin>>s;
    int a[1001],l,i,cnt=1;
    l=s.length();
    if (l==1)
    {
        cout<<1<<s[0];
    }
    
    for ( i = 0; i < l-1; i++)
    {
        if (s[i]==s[i+1])
        {
            cnt++;
            if (i+1==l-1)
            {
                cout<<cnt<<s[i];
            }
            
        }
        else
        {
            cout<<cnt<<s[i];
            cnt=1;
            if (i+1==l-1)
            {
                cout<<cnt<<s[i+1];
            }
            
        }
        
    }
    
}
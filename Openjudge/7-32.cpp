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
    for ( i = 0; i < l; i++)
    {
        if (s[i]<='z'&&s[i]>='a')
        {
            s[i]-=32;
        }        
    }
    if (l==1)
    {
        cout<<"("<<s[0]<<","<<1<<")";
    }
    

    
    for ( i = 0; i < l-1; i++)
    {
        if (s[i]==s[i+1])
        {
            cnt++;
            if (i+1==l-1)
            {
                cout<<"("<<s[i]<<","<<cnt<<")";
            }
            
        }
        else
        {
            cout<<"("<<s[i]<<","<<cnt<<")";
            cnt=1;
            if (i+1==l-1)
            {
                cout<<"("<<s[i+1]<<","<<cnt<<")";
            }
            
        }
        
    }
    
}
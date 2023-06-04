#include<bits/stdc++.h>
using namespace std;
int main()
{
    char s[205],c='\0',c_mx;
    int ct=0,l_mx=0,len;
    cin>>s;
    len=strlen(s);
    for (int i = 0; i <= len; i++)
    {
        if(s[i]==c)
            ct++;
        else{
            if(ct>l_mx){
                l_mx=ct;
                c_mx=c;
            }
            c=s[i];
            ct=1;
        }
    }
    cout<<c_mx<<" "<<l_mx;
    
    
    
}
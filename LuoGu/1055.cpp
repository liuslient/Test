#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
    string s;
    cin>>s;
    int l=s.length();
    int k=1,sum=0,i;
    for ( i = 0; i < l-1; i++)
    {
        if (s[i]=='-')
        {
            continue;
        }
        sum+=(s[i]-'0')*k;
        k++;
        
    }
    if(sum%11==10&&s[l-1]=='X'||sum%11==s[l-1]-'0')
    {
        cout<<"Right";
    }
    else
    {
        for ( i = 0; i < l-1; i++)
        {
            cout<<s[i];
        }
        if (sum%11==10)
        {
            cout<<"X";
        }
        else{
            cout<<sum%11;
        }
        
        
    }
    

}
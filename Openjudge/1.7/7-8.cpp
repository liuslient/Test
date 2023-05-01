#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s;
    char a,a_t;
    int i,n;
    cin>>s>>a>>a_t;
    for ( i = 0; i < s.length(); i++)
    {
        if (s[i]==a)
        {
            s[i]=a_t;
        }
        
    }
    cout<<s;
    
    
}
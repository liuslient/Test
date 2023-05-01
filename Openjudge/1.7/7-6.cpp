#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s;
    int i,n;
    cin>>s;
    if(s[0]>='0'&s[0]<='9')
        
        {cout<<"no";
        return 0;}
    for ( i = 0; i < s.length(); i++)
    {
        if (s[i]>='0'&s[i]<='9')
            continue;
        if (s[i]>='a'&s[i]<='z')
            continue;
        if (s[i]>='A'&s[i]<='Z')
            continue;
        if (s[i]=='_')
            continue;
        cout<<"no";
        return 0;
    }
    cout<<"yes";
    return 0;
}
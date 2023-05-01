#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s;
    int i,ans=0,a[26]={0};
    getline(cin,s);
    for ( i = 0; i < s.length(); i++)
    {
        a[s[i]-'a']++;
        
    }
    for ( i = 0; i < s.length(); i++)
    {
        if (a[s[i]-'a']==1)
        {
            cout<<s[i];
            return 0;
        }
        
        
    }
    cout<<"no";
     
}
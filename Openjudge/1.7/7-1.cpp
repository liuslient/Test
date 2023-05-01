#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s;
    int i,ans=0;
    getline(cin,s);
    for ( i = 0; i < s.length(); i++)
    {
        if (s[i]>='0'&&s[i]<='9')
        {
            ans++;
        }
        
    }
    cout<<ans;
     
}
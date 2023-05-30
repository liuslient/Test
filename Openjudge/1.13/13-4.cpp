#include<bits/stdc++.h>
using namespace std;
int main()
{
    int ct[26]={},len,t=4,mx=0;
    char s[85];
    while (t--)
    {
        cin.getline(s,85);
        len=strlen(s);
        for (int i = 0; i < len; i++)
        {
            if(s[i]>='A'&&s[i]<='Z')
            ct[s[i]-'A']++;
        }
        
    }
    for(int i=0;i<26;++i)
        mx=max(mx,ct[i]);
    for (int l = mx; l >= 1; --l)
    {
        for (int i = 0; i < 26; ++i)
        {
            if(ct[i]>=l)
                cout<<"* ";
            else
                cout<<"  ";
        }
        cout<<endl;
    }
    for(int i=0;i<26;++i)
        cout<<char(i+'A')<<" ";   
    
}
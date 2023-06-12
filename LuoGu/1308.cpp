#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s1,s2;
    cin>>s1;
    cin.ignore();
    getline(cin,s2);
    s1=" "+s1+" ";
    s2=" "+s2+" ";
    for (int i = 0; i < s1.size(); i++)
    {
        if(s1[i]>='a'&&s1[i]<='z'){
            s1[i]-=32;
        }
    }
    for (int i = 0; i < s2.size(); i++)
    {
        if(s2[i]>='a'&&s2[i]<='z'){
            s2[i]-=32;
        }
    }
    int cnt=0,pos=0;
    int first=s2.find(s1,pos);
    while (s2.find(s1,pos)!=-1)
    {
        cnt++;
        pos=s2.find(s1,pos)+1;
    }
    if(first==-1) cout<<-1;
    else cout<<cnt<<" "<<first;
    
}
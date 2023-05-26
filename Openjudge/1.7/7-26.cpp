#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
    string s[5];
    int idx=1;
    char ch;
    while (cin>>ch)
    {
        if (ch==',')
        {
            idx++;
            continue;
        }
        s[idx].append(1,ch);
    }
    int d1=s[1].find(s[2]);
    int d2=-1;
    while (s[1].find(s[3],d2+1)!=string::npos)
    {
        d2=s[1].find(s[3],d2+1);
    }
    int k=d2-d1-s[2].size();
    if (d1==-1||d2==-1||k<0)
    {
        cout<<-1;
    }
    else
        cout<<k;
}

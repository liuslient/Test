#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
    string s[100001];
    int idx=0;
    while (cin>>s[idx])
    {
        idx++;
    }
    for (int  i = idx-1; i >= 0; i--)
    {
        cout<<s[i]<<" ";
    }
    
    
}

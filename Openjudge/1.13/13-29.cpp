#include<bits/stdc++.h>
using namespace std;
int main()
{
    char s[1005];
    int c[128]={0},max=0,len;
    cin>>s;
    len=strlen(s);
    for (int i = 0; i < len; i++)
    {
        c[s[i]]++;
    }
    for (int i = 0; i < 128; i++)
    {
        if(c[i]>c[max]){
            max=i;
        }
    }
    cout<<char(max)<<' '<<c[max];
    
    
    
}
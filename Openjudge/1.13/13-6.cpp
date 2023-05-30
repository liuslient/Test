#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int len,a[301]={0},temp[301]={0},t=0,flag;
string s1,s2;
int main()
{
    cin>>s1;
    int len=s1.size();
    for (int i = 0; i < len; i++)
    {
        a[i]=s1[i]-'0';
    }
    s1=s1+s1;
    for (int i = 1; i <= len; i++)
    {
        for(int j=0;j<len;j++)
        {
            temp[j]=a[j];
        }
        for (int j = len-1; j >= 0; j--)
        {
            temp[j]=temp[j]*i+t;
            t=temp[j]/10;
            temp[j]=temp[j]%10;
        }
        s2="";
        for (int j = 0; j < len; j++)
        {
            s2=s2+(char)(temp[j]+'0');
        }
        flag=s1.find(s2,0);
        if(flag==-1)
        {
            cout<<0<<endl;
            return 0;
        }
        
        
    }
    cout<<1<<endl;
    
    
    
    
}
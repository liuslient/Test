#include <iostream>
#include <cstring>
#include <string.h>
using namespace std;

int process(char a[10000])
{
    int len=strlen(a);
    if(isdigit(a[0])!=0)
    {
        len++;
        for (int i = len; i > 0; i--)
        {
            a[i]=a[i-1];
        }
        a[0]='+';
        
    }
    bool flag=0;
    for (int i = 1; i < len; i++)
    {
        if (a[i]=='0'&&flag==0)
        {
            len--;
            for (int j = i; j <= len; j++)
            {
                a[j]=a[j+1];
            }
            i--;
            
        }
        else
        {
            flag=1;
        }
        
    }
    if(flag==0)
    {
        a[0]='0';
        len=1;
    }
    return len;
    
}
void out(char a[100],int l)
{
    bool flag=0;
    for(int i=1;i<l;i++)
    {
        if(a[i]!='0')
        {
            flag=1;
        }
    }
    if(flag==0)
    {
        cout<<"0"<<'\n';
    }
    else
    {
        if(a[0]=='+')
        {
            for (int i = 0; i < l; i++)
            {
                a[i]=a[i+1];
            }
            
        }
        cout<<a;
    }
}
int main()
{
    int n;
    cin>>n;
    char s[100][100];
    int length[100],num[100];
    memset(num,0,400);
    for (int i = 0; i < n; i++)
    {
        cin>>s[i];
        length[i]=process(s[i]);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (length[i]==length[j])
            {
                bool flag=0;
                for (int k = 0; k < length[i]; k++)
                {
                    if(s[i][k]!=s[j][k])
                    {
                        flag=1;
                    }
                }
                if(flag==0)
                {
                    num[i]++;
                }
                
            }
            
        }
        
    }
    int max1=num[0],max2=0;
    for (int i = 1; i < n; i++)
    {
        if(num[i]>max1)
        {
            max1=num[i];
            max2=i;
        }
    }
    if (max1==n)
    {
        cout<<"no"<<'\n';
    }
    else
    {
        out(s[max2],length[max2]);
    }
    
    
    
    
}
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string.h>
using namespace std;
int main()
{
    char s[10001],a[10001],b[10001],c[10001];
    int i,n,l,flag=0,j;
    cin>>s;
    cin>>n;
    for ( i = 1; i <= n; i++)
    {
        cin>>a>>b>>c;
        if(strcmp(s,c)==0)
        {
            l=strlen(b);
            for ( j = 0; j < l; j++)
            {
                if (b[j]>=65&&b[j]<=90)
                {
                    b[j]+=32;
                } 
                else if (b[j]>=97&&b[j]<=122)
                {
                    b[j]-=32;
                }
                
            }
            cout<<a<<" "<<b<<endl;
            flag++;
            
        }
    }
    if (flag==0)
    {
        cout<<"empty";
        return 0;
    }
    
    
}
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    string x,y;
    int a[1000001],b[1000001],c[1000001],la,lb,lc,i,n;
    cin>>n>>x>>y;
    la=x.length();
    lb=y.length();
    for ( i = 0; i < la; i++)
    {
        if(x[i]>='A'&&x[i]<='Z')
        {
            a[la-i]=x[i]-'A'+10;
        }
        else
        {
            a[la-i]=x[i]-'0';
        }
        
        
    }
    for ( i = 0; i < lb; i++)
    {
        if(y[i]>='A'&&y[i]<='Z')
        {
            b[lb-i]=y[i]-'A'+10;
        }
        else
        {
            b[lb-i]=y[i]-'0';
        }
        
    }
    lc=max(la,lb);
    for ( i = 1; i <= lc; i++)
    {
        c[i]+=a[i]+b[i];
        c[i+1]+=c[i]/n;
        c[i]%=n;
    }
    if(c[lc+1]>0)
    {
        lc++;
    }
    for (i=lc; i >= 1; i--)
    {
        if (c[i]>=10)
        {
            cout<<char(c[i]-10+'A');
        }
        else
            {cout<<c[i];}
    }
    
    
}
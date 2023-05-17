#include <iostream>
#include <cstring>
using namespace std;

char a1[555],b1[555];
int a[555],b[555],c[555],i,x,la,lb,lc;

int main()
{
    cin >> a1;
    cin >> b1;
    la=strlen(a1);
    lb=strlen(b1);
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(c,0,sizeof(c));

    for ( i = 0; i < la; i++)
    {
        a[la-i]=a1[i]-'0';
    }
    for ( i = 0; i < lb; i++)
    {
        b[lb-i]=b1[i]-'0';
    }
    lc=max(la,lb);
    for ( i = 1; i <= lc; i++)
    {
        c[i]+=a[i]+b[i];
        c[i+1]=c[i]/10;
        c[i]%=10;
    }
    if (c[lc+1]>0)
    {
        lc++;
    }
    for ( i = lc; i >= 1; i--)
    {
        cout<<c[i];
    }
   
}
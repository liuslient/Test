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
    x=0;
    lc=1;
    while (lc<=la||lc<=lb)
    {
        c[lc]=a[lc]+b[lc]+x;
        x=c[lc]/10;
        c[lc]%=10;
        lc++;
    }
    c[lc]=x;
    while (c[lc]==0&&lc>1)
    {
        lc--;
    }
    for ( i = lc; i >=1; i--)
    {
        cout<<c[i];
    }
    

    
    
    
}
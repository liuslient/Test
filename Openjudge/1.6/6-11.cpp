#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
    string a1,b1;
    int a[250],b[250],c[250],i,x,la,lb,lc;
    cin>>a1>>b1;
    la=a1.length();
    lb=b1.length();
    for ( i = 0; i < la; i++)
    {
        a[la-i]=a1[i]-'0';
    }
    for ( i = 0; i < lb; i++)
    {
        b[lb-i]=b1[i]-'0';
    }
    for ( i = 1; i <= la; i++)
    {
        if (a[i]<b[i])
        {
            a[i]+=10;
            a[i+1]--;
        }
        c[i]=a[i]-b[i];
        
    }
    while(c[la]==0&&la>1)
    {
        la--;
    }
    for ( i = la; i >= 1; i--)
    {
        cout<<c[i];
    }
    
    
    
}

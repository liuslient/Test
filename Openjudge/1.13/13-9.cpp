#include <iostream>
#include <cstring>
using namespace std;

string a1,b1;
int a[100001],b[100001],c[100001],i,j,x,la,lb,lc;

int main()
{
    cin >> a1;
    cin >> b1;
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
        for ( j = 1; j <= lb; j++)
        {
            c[i+j-1]+=a[i]*b[j];
            c[i+j]+=c[i+j-1]/10;
            c[i+j-1]%=10;
        }
    }
    lc=la+lb;
    while(c[lc]==0&&lc>1)
    {
        lc--;
    }    
    for ( i = lc; i >= 1; i--)
    {
        cout<<c[i];
    }
    
}
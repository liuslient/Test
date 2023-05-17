#include <iostream>
#include <cstring>
using namespace std;

string a1,b1;
int a[100001],b[100001],c[100001],i,x,la,lb,lc;

int main()
{
    cin >> a1;
    cin >> b1;
    la=a1.length();
    lb=b1.length();
    if(la<lb || la==lb&&a1<b1)
    {
        swap(a1,b1);
        swap(la,lb);
        cout<<'-';
    }
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
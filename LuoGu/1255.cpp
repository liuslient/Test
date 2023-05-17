#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    int ans=0,i,n,a[5005],b[5005],c[5005],lc=1,j;
    a[1]=1;
    b[1]=2;
    cin>>n;
    for ( i = 3; i <=n; i++)
    {
        memset(c,0,sizeof(c));
        for ( j = 1; j <= lc; j++)
        {
            c[j]+=a[j]+b[j];
            c[j+1]=c[j]/10;
            c[j]%=10;
        }
        if (c[lc+1]>0)lc++;
        for ( j = 1; j <= lc; j++)
        {
            a[j]=b[j];
        }
        for ( j = 1; j <= lc; j++)
        {
            b[j]=c[j];
        }
        
    }
    for ( i = lc; i >= 1; i--)
    {
        cout<<c[i];
    }
}
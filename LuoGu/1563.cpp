#include<iostream>
#include<math.h>
#include<string.h>
#include<algorithm>

using namespace std;

int main()
{
    int n,m,i;
    cin>>n>>m;
    int a[n+10];
    string b[n+10];
    for ( i = 0; i < n; i++)
    {
        cin>>a[i]>>b[i];
        if (a[i]==0)
        {
            a[i]=1;
        }
        else
        {
            a[i]=-1;
        }
        
    }
    int p=0;
    while (m--)
    {
        int x,y;
        cin>>x>>y;
        if(x==0)
            x=-1;
        p+=y*a[p]*x;
        p+=n;
        p%=n;
    }
    cout<<b[p];
}                 
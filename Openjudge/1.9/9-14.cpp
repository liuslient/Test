#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;

int main()
{
    int n,i,x,y;
    cin>>n;
    int a[n+10],b[n+10],j[n+10],k[n+10];
    for ( i = 1; i <= n; i++)
    {
        cin>>a[i]>>b[i]>>j[i]>>k[i];
    }
    cin>>x>>y;
    for ( i = n; i >=1 ; i--)
    {
        if(a[i]<=x&&b[i]<=y&&a[i]+j[i]>=x&&b[i]+k[i]>=y)
        {
            cout<<i;
            return 0;
        }
    }
    cout<<-1;
    
}
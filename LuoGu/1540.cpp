#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;

int main()
{
    int m,n,i,ans=0;
    cin>>m>>n;
    int a[n+10];
    int q[n+10];
    int b[1001]={0};
    for ( i = 1; i <= n; i++)
    {
        cin>>a[i];
    }
    int head=1,tail=0;
    for ( i = 1; i <= n; i++)
    {
        if (!b[a[i]])
        {
            q[++tail]=a[i];
            b[a[i]]=1;
        }
        if (tail-head>=m)
        {
            b[q[head]]=0;
            head++;
        }
    }
    cout<<tail;
}
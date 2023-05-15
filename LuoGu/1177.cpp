#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;
int main()
{
    int n,i;
    cin>>n;
    int a[n+10];
    for ( i = 0; i < n; i++)
    {
        cin>>a[i];
    }
    sort(a,a+n);
    for ( i = 0; i < n; i++)
    {
        cout<<a[i]<<" ";
    }
}
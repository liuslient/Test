#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;

int main()
{
    int m,n,i,j,k;
    int num[6000],a[6000];
    cin>>n>>m;
    for ( i = 1; i <= n; i++)
    {
        cin>>num[i]>>a[i];
    }
    for ( i = 1; i < n; i++)
    {
        for ( j = 1; j <= n-i; j++)
        {
            if (a[j]<a[j+1] || a[j]==a[j+1]&&num[j]>num[j+1])
            {
                swap(a[j],a[j+1]);
                swap(num[j],num[j+1]);
            }
        }
        
    }
    k=m*1.5;
    int ren=0;
    while (a[++ren]>=a[k]);
    ren--;
    cout<<a[k]<<" "<<ren<<endl;
    for ( i = 1; i <= ren; i++)
    {
        cout<<num[i]<<" "<<a[i]<<endl;
    }  
}
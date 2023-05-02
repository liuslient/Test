#include <iostream>
#include<iomanip>
#include<cmath>
using namespace std;
int main()
{
    int i,j,n,k;
    cin>>n;
    int num[n+10],yw[n+10],sx[n+10],wy[n+10],sum[n+10];
    for ( i = 1; i <= n; i++)
    {
        num[i]=i;
        cin>>yw[i]>>sx[i]>>wy[i];
        sum[i]=yw[i]+sx[i]+wy[i];
    }

    for ( i = 1; i < n; i++)
    {
        for ( j = 1; j<=n-i; j++)
        {
            if (sum[j]<sum[j+1] || sum[j]==sum[j+1]&&yw[j]<yw[j+1] || sum[j]==sum[j+1]&&yw[j]==yw[j+1]&&num[j]>num[j+1])
            {
                swap(num[j],num[j+1]);
                swap(sum[j],sum[j+1]);
                swap(yw[j],yw[j+1]);
                swap(sx[j],sx[j+1]);
                swap(wy[j],wy[j+1]);
            }
            
            
        }
    }
    for ( i = 1; i <= 5; i++)
    {
        cout<<num[i]<<" "<<sum[i]<<endl;
    }
}
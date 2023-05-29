#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,i;
    double sum=0,cost;
    cin>>n;
    int a[n+10];
    for ( i = 1; i <= n; i++)
    {
        cin>>a[i];
        if(a[i]%70==0)
        {
            int t=a[i]/70;
            sum+=t*0.1;
        }
        else
        {
            int t=a[i]/70+1;
            sum+=t*0.1;
        }
    }
    printf("%.1lf",sum);
    
}
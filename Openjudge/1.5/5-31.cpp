#include<iostream>
using namespace std;
int a[5001];

int main()
{
    int n,m,i,j;
    cin>>n>>m;
    for ( i = 1; i <= n; i++)
    {
        a[i]=1;
    }
    for ( i = 1; i <= m; i++)
    {
        for ( j = 1; j <=n; j++)
        {
            if(j%i==0)
            {
                a[j]=-a[j];
            }
        }
        
    }
    int sta=0;
    for ( i = 1; i <= n; i++)
    {
        if(a[i]<0&&sta==1)
            cout<<","<<i;
        if(a[i]<0&&sta==0)
            cout<<i;
            sta=1;
    }
    

}
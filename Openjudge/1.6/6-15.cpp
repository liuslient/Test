#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int a[100001]={1,1},n,sum[100001]={1};

void fact(int n);
void add();
int main()
{
    //a[0]是位数
    cin>>n;
    for (int i = 1; i <= n; i++)
    {
        fact(i);
        add();
    }
    for (int i = sum[0]; i>=1; i--)
    {
        cout<<sum[i];
    }

}

void fact(int n)
{
    int k=0;
    for ( int j = 1; j <= a[0]; j++)
    {
        a[j]=a[j]*n+k;
        k=a[j]/10;
        a[j]%=10;
    }
    while (k)
    {
        a[++a[0]]=k%10;
        k/=10;
    }
   
}
void add()
{
    if(a[0]>sum[0])
        sum[0]=a[0];
    int k=0;
    for (int i = 1; i <= sum[0]; i++)
    {
        sum[i]=sum[i]+a[i]+k;
        k=sum[i]/10;
        sum[i]%=10;
    }
    if(k)
    {
        sum[++sum[0]];
    }
    
}
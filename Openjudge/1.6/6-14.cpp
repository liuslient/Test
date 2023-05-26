#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int main()
{
    int a[100001]={1,1},n,i,j;
    //a[0]是位数
    cin>>n;
    for ( i = 1; i <= n; i++)
    {
        int k=0;
        for ( j = 1; j <= a[0]; j++)
        {
            a[j]=a[j]*i+k;
            k=a[j]/10;
            a[j]%=10;
        }
        while (k)
        {
            a[++a[0]]=k%10;
            k/=10;
        }
        
        
    }
    for ( i = a[0]; i>=1; i--)
    {
        cout<<a[i];
    }
    
    
}

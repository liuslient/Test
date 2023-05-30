#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
double ans;
char a[1001];
int main()
{
    double zs=1;
    double cs;
    cin>>a;
    int l=strlen(a);
    for (int i = 2; i < l; i++)
    {
        cs=pow(8,zs);
        zs++;
        ans=ans+(double)(a[i]-48)/cs;
    }
    printf("%s [8] = %.45g [10]",a,ans);
    
}
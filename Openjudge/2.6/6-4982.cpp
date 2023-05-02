#include<stdio.h>
int f[25];
int main()
{
    int n;
    scanf("%d",&n);
    f[1]=3, f[2]=7;
    for (int i=3;i<=n;i++)
        f[i]=2*f[i-1]+f[i-2];
    printf("%d\n",f[n]);
    return 0;

}
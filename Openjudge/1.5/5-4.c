#include<stdio.h>
int main()
{
    int i,n=0,a[10001],sum=0;
    double s=0;
    scanf("%d",&n);
    for (i = 0; i < n; i++)
    {
        scanf("%d",&a[i]);
        sum+=a[i];
    }
    s=1.0*sum/n; 
    printf("%d %.5f",sum,s);
}
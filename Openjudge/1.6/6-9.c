#include<stdio.h>
#include<math.h>
#define N 100001
int main()
{
    int n,a[N],b[N],i,sum=0;
    scanf("%d",&n);
    for ( i = 0; i < n; i++)
    {
        scanf("%d",&a[i]);
    }
    for ( i = 0; i < n; i++)
    {
        scanf("%d",&b[i]);
    }
    for ( i = 0; i < n; i++)
    {
        sum+=a[i]*b[i];
    }
    printf("%d",sum);
    
}
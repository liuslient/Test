#include<stdio.h>
int main()
{
    int i,n,sum=0,a,s;
    scanf("%d",&n);
    for (i = 0; i < n-1; i++)
    {
        scanf("%d",&a);
        sum+=a;
    }
    s=(n-2)*180-sum;
    printf("%d",s);
}
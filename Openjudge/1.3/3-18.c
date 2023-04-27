#include<stdio.h>
int main()
{
    int a,b,n,sum;
    scanf("%d %d %d",&a,&b,&n);
    sum=(b-a)*(n-1)+a;
    printf("%d",sum);
}
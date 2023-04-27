#include<stdio.h>
int main()
{
    int n,g,s,b;
    scanf("%d",&n);
    b=n/100;
    s=n/10%10;
    g=n%10;
    printf("%d%d%d",g,s,b);
}
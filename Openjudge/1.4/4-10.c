#include<stdio.h>
int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    if (a <60&&b>59||b<60&&a>59)
        printf("1");
    else
        printf("0");
}
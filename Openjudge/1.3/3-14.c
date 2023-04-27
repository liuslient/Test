#include<stdio.h>
#include<math.h>
#define pi 3.14159
int main()
{
    int n,h,r;
    float l;
    scanf("%d %d",&h,&r);
    l=pi*r*r*h/1000.0;
    n=ceil(20/l);
    printf("%d",n);
}
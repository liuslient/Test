#include<stdio.h>
int main()
{
    double a,b,c,d,x,sum;
    scanf("%lf %lf %lf %lf %lf",&x,&a,&b,&c,&d);
    sum=a*x*x*x+b*x*x+c*x+d;
    printf("%.7lf",sum);
}
#include<stdio.h>
int main()
{
    double a,b;
    scanf("%lf %lf",&a,&b);
    double c=b/a*100;
    printf("%.3lf",c);
    printf("%%");
}
#include<stdio.h>
#include<math.h>
#define pi 3.14
int main()
{
    double r,k;
    scanf("%lf",&r);
    k=(4/3.0)*pi*r*r*r;
    printf("%.2lf",k);
}
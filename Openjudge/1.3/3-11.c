#include<stdio.h>
#include<math.h>
int main()
{
    double a,b,r,k;
    scanf("%lf %lf",&a,&b);
    r=a-floor(a/b)*b;//向下取整
    printf("%g",r);
}
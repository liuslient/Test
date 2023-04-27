#include<stdio.h>
#define pi 3.14159
int main()
{
    float r,r1,r2;
    scanf("%f %f",&r1,&r2);
    r=1/(1/r1+1/r2);
    printf("%.2f",r);
}
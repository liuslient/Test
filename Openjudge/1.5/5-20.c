#include<stdio.h>
#include<math.h>
int main()
{
    int i;
    double h,high=0,sum=0;
    scanf("%lf",&h);
    high=h;
    for(i=1;i<=10;i++)
    {
        sum+=high*2;
        high=high/2.0;
    }
    printf("%g\n%g",sum-h,high);
    
}
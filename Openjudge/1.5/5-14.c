#include<stdio.h>
#include<math.h>
int main()
{
    int x,n,i;
    double sum,z=0;
    scanf("%d %d",&x,&n);
    sum=x;
    for (i = 0; i < n; i++)
    {
        sum=sum*(1+0.001);
    }
    printf("%.4lf",sum);
}
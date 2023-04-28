#include<stdio.h>
#include<math.h>
int main()
{
    int r,m,y,i,z;
    double sum;
    scanf("%d %d %d",&r,&m,&y);
    sum=m;
    for (i = 0; i < y; i++)
    {
        sum=sum*(1+r*0.01);
    }
    z=floor(sum);
    printf("%d",z);
}
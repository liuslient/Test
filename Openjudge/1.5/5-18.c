#include<stdio.h>
int main()
{
    int n,a,b,i;
    double x,y[20];
    scanf("%d",&n);
    scanf("%d %d",&a,&b);
    x=1.0*b/a;
    for (i = 2; i <= n; i++)
    {
        scanf("%d %d",&a,&b);
        y[i]=1.0*b/a;
    }
    for (i = 2; i <= n; i++)
    {
        if(y[i]-x>0.05)
            printf("better\n");
        else if(y[i]-x<-0.05)
            printf("worse\n");
        else
            printf("same\n");
    }
    
}
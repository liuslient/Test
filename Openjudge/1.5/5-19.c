#include<stdio.h>
#include<math.h>
int main()
{
    int n,m,z;
    float x,y,s=0;
    scanf("%d",&n);
    
    for (int i = 1; i <= n; i++)
    {
        scanf("%f %f %d",&x,&y,&m);
        s+=2.0*sqrt(x*x+y*y)/50+1.5*m;
    }
    z=ceil(s);
    printf("%d",z);
}
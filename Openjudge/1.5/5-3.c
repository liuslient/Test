#include<stdio.h>
int main()
{
    int n;
    float s,a,sum=0;
    scanf("%d\n",&n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%f",&a);
        sum+=a;
    }
    s=1.0*sum/n; 
    printf("%.4f",s);
}
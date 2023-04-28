#include<stdio.h>
int main()
{
    float n,sum=0,s;
    for (int i = 1; i <= 12; i++)
    {
        scanf("%f\n",&n);
        sum+=n;
    }
    s=sum/12.0; 
    printf("$");
    printf("%.2f",s);
}

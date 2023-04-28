#include<stdio.h>
int main()
{
    int n,a,sum=0;
    float s;
    scanf("%d\n",&n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d\n",&a);
        sum+=a;
    }
    s=1.0*sum/n; 
    printf("%.2f",s);
}

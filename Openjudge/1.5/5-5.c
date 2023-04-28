#include<stdio.h>
int main()
{
    int i,n,max=0,a;
    scanf("%d",&n);
    for (i = 0; i < n; i++)
    {
        scanf("%d",&a);
        if(max<a)
            max=a;
    }
    printf("%d",max);
}
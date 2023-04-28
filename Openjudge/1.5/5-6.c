#include<stdio.h>
int main()
{
    int i,n,max=-1,a,min=1001;
    scanf("%d",&n);
    for (i = 0; i < n; i++)
    {
        scanf("%d",&a);
        if(max<=a)
            max=a;
        if(min>=a)
            min=a;
    }
    printf("%d",max-min);
}
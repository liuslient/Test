#include<stdio.h>
int main()
{
    int i,n,m,sum=0,a;
    scanf("%d %d",&m,&n);
    for (i = m; i <= n; i++)
    {
        if(i%2!=0)
            sum+=i;
    }
    printf("%d",sum);
}
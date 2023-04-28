#include<stdio.h>
int main()
{
    int i,N,m,a,sum=0;
    scanf("%d %d",&N,&m);
    for (i = 0; i < N; i++)
    {
        scanf("%d",&a);
        if(m==a)
            sum+=1;
    }
    printf("%d",sum);
}
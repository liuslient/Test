#include<stdio.h>
int main()
{
    int i,k,n,yi=0,wu=0,shi=0;
    scanf("%d",&k);
    for (i = 0; i < k; i++)
    {
        scanf("%d",&n);
        if(n==1)
            yi+=1;
        if(n==5)
            wu+=1;
        if(n%10==0)
            shi+=1;
    }
    printf("%d\n%d\n%d",yi,wu,shi);
}
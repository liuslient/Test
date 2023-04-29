#include<stdio.h>
int main()
{
    int i,num[100],n;
    scanf("%d",&n);
    for ( i = 0; i < n; i++)
    {
        scanf("%d",&num[i]);
    }
    while (n>0)
    {
        printf("%d ",num[n-1]);
        n--;
    }    
    
    
}
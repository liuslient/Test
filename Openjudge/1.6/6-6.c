#include<stdio.h>
int main()
{
    int l,m,i,a[10001],q,z,j,sum=0;
    scanf("%d %d",&l,&m);
    for ( i = 0; i <= l; i++)
    {
        a[i]=1;
    }
    for ( i = 0; i < m; i++)
    {
        scanf("%d %d",&q,&z);
        for ( j = q; j <= z; j++)
        {
            a[j]=0;
        }
        
    }
    for ( i = 0; i <= l; i++)
    {
        if(a[i])
            sum++;
    }
    printf("%d",sum);
    
    
    
}
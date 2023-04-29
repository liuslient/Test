#include<stdio.h>
#include<math.h>
#define N 3000
int main()
{
    int n,i,j=0,biao=0;
    long int a[N],b[N],c[N];
    scanf("%d",&n);
    for ( i = 0; i < n; i++)
    {
        scanf("%d",&a[i]);
    }
    for ( i = 0; i < n-1; i++)
    {
        b[i]=abs(a[i+1]-a[i]);
    }

    for ( i = n-1; i >=0; i--)
    {
        c[i]=b[j];
        j++;
    }
    for ( i = 0; i < n-1; i++)
    {
        if (c[i]!=i)
        {
            printf("Not jolly");
            return 0;
        }
        
    }
    printf("Jolly");
}
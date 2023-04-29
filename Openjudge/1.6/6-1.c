#include<stdio.h>
int main()
{
    int n,a[100],m,i,j=0;
    scanf("%d",&n);
    for (i = 0; i < n; i++)
    {
        scanf("%d",&a[i]);
    }
    scanf("%d",&m);
    for ( i = 0; i < n; i++)
    {
        if (a[i]==m)
        {
            j++;
        }
        
    }
    printf("%d",j);
    
    
}
#include<stdio.h>
int main()
{
    int d_high=30,high[10],r_high,i,j=0;
    for (i = 0; i < 10; i++)
    {
        scanf("%d",&high[i]);
    }
    scanf("%d",&r_high);
    for ( i = 0; i < 10; i++)
    {
        if(r_high+d_high>=high[i])
        {
            j++;
        }
        
    }
    printf("%d",j);
    
    
}
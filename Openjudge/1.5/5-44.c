#include<stdio.h>
#include<math.h>
int main()
{
    int n,i,a=0,j,prime,d;
    scanf("%d",&n);
    d=1;
    for ( i = 3;d!=n ; i++)
    {
        prime=1;
        for ( j = 2; j <= sqrt(i); j++)
        {
            if(i%j==0)
            {
                prime=0;
                break;
            }
        }
        if (prime)
        {
            d++;
        }
    }
    printf("%d",i-1);
}
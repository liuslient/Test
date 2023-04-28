#include<stdio.h>
#include<math.h>
int main()
{
    int n,k,i=1;
    double house=200,sum;
    scanf("%d %d",&n,&k);
    sum=n;
    while(sum<house)
    {
        i++;
        sum+=n;
        house=house*(1+k*0.01);
        if(i>20)
        {
            printf("Impossible");
            break;
        }
    }
    if(sum>=house)
        printf("%d",i);
}
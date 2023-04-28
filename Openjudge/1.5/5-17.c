#include<stdio.h>
#include<math.h>
int main()
{
    int n,k,i=2,a=1,b=1,sum;
    scanf("%d",&k);
    if(k==1||k==2)
        sum=1;
    while(i<k&&k>2)
    {
        sum=a+b;
        a=b;
        b=sum;
        i++;
    }
    printf("%d",sum);
}
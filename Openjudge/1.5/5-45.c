#include<stdio.h>
#include<math.h>
int main()
{
    int i,time,sum=0,send=1;
    scanf("%d",&time);
    while(time>0)
    {
        if(time>send)
        {
            sum+=send*send;
            time=time-send;
        }
        else
        {
            sum+=send*time;
            time=0;
        }
        send++;
    }
    printf("%d",sum);
}
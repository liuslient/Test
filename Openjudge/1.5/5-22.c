#include<stdio.h>
#include<math.h>
int main()
{
    long int i,N;
    scanf("%d",&N);
    while(N!=1)
    {
        if(N%2!=0)
            {printf("%ld*3+1=%ld\n",N,N*3+1);
            N=N*3+1;}
        else
            {printf("%ld/2=%ld\n",N,N/2);
            N=N/2;}
    }
    printf("End");
    
}
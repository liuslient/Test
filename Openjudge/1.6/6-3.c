#include<stdio.h>
int main()
{
    int i,num[10];
    float fei=0;
    float dan[]={28.9,32.7,45.6,78,35,86.2,27.8,43,56,65};
    for ( i = 0; i < 10; i++)
    {
        scanf("%d",&num[i]);
        fei+=num[i]*dan[i];
    }
    printf("%.1f",fei);
    
    
    
}
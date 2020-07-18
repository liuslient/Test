#include<stdio.h>
int main()
{
        int d1,d2,d3,a,b,c,d,n,m,h;
        scanf("%d %d %d",&d1,&d2,&d3);
        a=d1+d2+d3;
        b=(d1+d2)*2;
        c=(d1+d3)*2;
        d=(d3+d2)*2;
        n=(a>b)?b:a;
        m=(c>d)?d:c;
        h=(n>m)?m:n;
        printf("%d",h);
}


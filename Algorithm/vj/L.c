#include<stdio.h>
int main()
{
        int n,a,b,s;
        while(~scanf("%d",&n))
        {
                a=n/2;
                b=n-a;
                s=a*(a-1)/2+b*(b-1)/2;
                printf("%d\n",s);
        }
}

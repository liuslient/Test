#include<stdio.h>
int sanjiao(int n);
int main()
{
        int a,b,i,j;
        while(~scanf("%d",&a))
        {
                sanjiao(a);
                printf("\n");
        }

}
int sanjiao(int n)
{
        int i,j;
        int h[30]={1};
        for(i=0;i<n;i++)
        {
                for(j=i;j>0;j--)
                        h[j]=h[j]+h[j-1];
                for(j=0;j<=i;j++)
                        if(j==i)
                                printf("%d",h[j]);
                        else
                                printf("%d ",h[j]);
                printf("\n");
        }
}

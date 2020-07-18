#include<stdio.h>
int main()
{
        int n,m,i,j,w=0;
        int h[100];
        scanf("%d",&m);
        for(j=0;j<m;j++)
        {
                while(scanf("%d",&n)!=EOF&&n!=0)
        {
                w=0;
                for(i=0;i<n;i++)
                {
                        scanf("%d",&h[i]);
                        w+=h[i];
                }
                printf("%d\n",w);
        }
        }
}

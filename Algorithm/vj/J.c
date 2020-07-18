#include<stdio.h>
int main()
{
        int n,i,j=0,t,x,s,w=0;
        int h[1000][2];
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
                scanf("%d %d",&h[i][0],&h[i][1]);
        }
        for(i=0;i<n;i++)
        {
                w+=h[i][1]-h[i][0];
                if(w>j)
                {
                        j=w;
                }
        }
        printf("%d",j);
}

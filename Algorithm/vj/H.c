#include<stdio.h>
int main()
{
        int n,i,j,w=0;
        scanf("%d",&n);
        int h[1000][3];
        for(i=0;i<n;i++)
        {
                for(j=0;j<3;j++)
                {
                        scanf("%d",&h[i][j]);
                }
        }
        for(i=0;i<n;i++)
        {
                if((h[i][0]==1&&h[i][1]==1)||(h[i][0]==1&&h[i][2]==1)||(h[i][2]==1&&h[i][1]==1))
                        w++;
        }

         printf("%d",w);
}

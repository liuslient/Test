#include<stdio.h>
int main()
{
        int n,k,i,j=0;
        char h[100];
        scanf("%d %d",&n,&k);
        for(i=0;i<n;i++,j++)
        {
                if(j==k)
                        j=0;
                h[i]='a'+j;
        }
        for(i=0;i<n;i++)
        {
                printf("%c",h[i]);
        }

}

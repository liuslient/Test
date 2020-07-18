#include<stdio.h>
#include<string.h>
int main()
{
        int n,w,i,k;
        char h[100];
        scanf("%d",&n);
        while(n--)
        {
                w=0;
                scanf("%s",&h);
                k=strlen(h);
                for(i=0;i<k;i++)
                        if(h[i]<'A')
                                w++;
                printf("%d\n",w);
        }
}

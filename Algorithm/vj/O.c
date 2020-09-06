#include<stdio.h>
int main()
{
        char h[1001];
        int l,i,n;
        while(scanf("%s",h)&&strcmp(h,"0")!=0)
        {
                l=strlen(h);
                n=0;
                for(i=0;i<l;i++)
                        n+=h[i]-'0';
                printf("%d\n",(n-1)%9+1);
        }
        return 0;
}

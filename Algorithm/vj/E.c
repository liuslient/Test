#include <stdio.h>
int main()
{
    int a,i,w,j,m,n;
    scanf("%d",&m);
    for(i=0;i<m;++i)
    {
        w=0;
        scanf("%d",&n);
        for(j=0;j<n;++j)
        {
            scanf("%d",&a);
            w+=a;
        }
        printf("%d\n",w);
        if(m!=i+1)
        {
            printf("\n");
        }
    }
    return 0;
}


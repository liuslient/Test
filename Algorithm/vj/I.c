#include<stdio.h>
int main()
{
    int n,k,i,w[100],g,h;
    while(scanf("%d %d",&n,&k)!=EOF)
    {
	    g=1;h=0;
	    for(i=0;i<n;i++)
	    {
		    scanf("%d",&w[i]);
		    if(w[i]>k)
			    g=0;
            }
	    if(g==1)
		    printf("%d\n",n);
	    else
	    {
		    for(i=0;i<n;i++)
		    {
			    if(w[i]<=k)
				    h++;
			    else
				    break;
                    }
		    for(i=n-1;i>=0;i--)
		    {
			    if(w[i]<=k)
				    h++;
			    else
				    break;
                    }
		    printf("%d\n",h);
              }
    }
    return 0;
}

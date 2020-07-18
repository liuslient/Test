#include<stdio.h>
int main()
{
	char h[100];
	int j,i;
	while(gets(h))
	{
		j=strlen(h);
		for(i=0;i<j;i++)
		{ 
		       if(i==0)
			       h[0]=h[0]-32;
		       if(h[i]==' ')
			       h[i+1]=h[i+1]-32;
		       printf("%c",h[i]);
		}
		printf("\n");
	}
	return 0;
}

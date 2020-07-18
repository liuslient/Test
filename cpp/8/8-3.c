#include<stdio.h>
int main()
{
	char c;
	int n=0,m=0;
	while((c=getchar())!='&')
	{
		if(c>'a'&&c<'z')
		{
			n++;
		}
		else if(c>'A'&&c<'Z')
		{
			m++;
		}
	}
	printf("%d\n%d",n,m);
}

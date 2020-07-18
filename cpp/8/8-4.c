#include<stdio.h>
int main()
{
	char c;
	int n=1,m=0,z,h;
	while((c=getchar())!='\n')
	{
		if(c==' ')
		{
			n++;
		}
		m++;
	}
	z=m-n;
	h=z/n;
	printf("%d\n",h);
}


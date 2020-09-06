#include<stdio.h>
int main()
{
	char c;
	int n=0;
	while((c=getchar())!='&')
	{
		n++;
	}
	printf("%d",n);
}

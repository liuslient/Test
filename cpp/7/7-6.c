#include<stdio.h>
int main()
{
	char h;
	int a=0;
	while((h=getchar())!='#')
	{
		if(h=='e')
		{
			continue;
		}
		if(h=='i')
		{
			a++;
		}
	}
	printf("%d",a);
}

#include<stdio.h>
int main()
{
	char h;
	while((h=getchar())!='#')
	{
		if(h=='.')
		{
			a++;
			putchar('!');
		}
		else if(h=='!')
		{
			a++;
			putchar('!');
		        putchar('!');
		}
		else
		{
			putchar(h);
		}
	}
}

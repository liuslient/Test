#include<stdio.h>
int main()
{
	char h;
	int a=0,b=0,c=0;
	while((h=getchar())!='#')
	{
		if(h==' ')
			a++;
		else if(h=='\n')
			b++;
		else
			c++;
	}
	printf("空格:%d换行:%d其他:%d",a,b,c);
}

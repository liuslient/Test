#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main()
{
	char ch[1000];
	int a=0,b=0,c=0,d=0,e=0,i;
	scanf("%s",ch);
	a=strlen(ch);
	for(i=0;i<=a;i++)
	{
		if(isupper(ch[i]))
		{
			b++;
		}
		else if(islower(ch[i]))
		{
			c++;
		}
		else if(ispunct(ch[i]))
		{
			d++;
		}
		else if(isalnum(ch[i]))
		{
			e++;
		}
	}
	printf("单词数%d\n大写数%d\n小写数%d\n标点数%d\n数字数%d\n",a,b,c,d,e);
}

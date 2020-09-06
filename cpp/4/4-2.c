#include<stdio.h>
int main()
{
	char a[10];
	printf("请输入名字:");
	scanf("%s",a);
	printf("%s\n",a);
	printf("%20s\n",a);
	printf("%-20s\n",a);
	int m=strlen(a);
	printf("%*s",m+3,a);
}

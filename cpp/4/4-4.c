#include<stdio.h>
int main()
{
	float n;
	char c[20];
	printf("请输入身高:");
	scanf("%f",&n);
	printf("请输入名字:");
	scanf("%s",c);
	printf("%s,you are %.2f cm tall",c,n);
}

#include<stdio.h>
int main()
{
	int n,m,h;
	printf("请输入天数:");
	scanf("%d",&n);
	while(n>0)
	{
		m=n%7;
		h=n/7;
		printf("%d days are %d weeks, %d days",n,h,m);
		scanf("%d",&n);
	}
}

#include<stdio.h>
int main()
{
	double n=3.0e-23,m=950,h,j;
	printf("请输入水的夸脱数:");
	scanf("%f",&h);
	j=h*m/n;
	printf("水分子数量:%e",j);

}

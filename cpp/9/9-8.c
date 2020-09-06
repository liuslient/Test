#include<stdio.h>
double power(double n,int p)
{
	int i;
	double h=1;
	if(p==0)
	{
		if(n==0)
		{
			printf("0");
		}
		h=1.0;
	}
	else if(n==0)
	{
		h=0.0;
	}
	else if(p>0)
	{
		for(i=1;i<=p;i++)
		{
			h*=n;
		}
	}
	else
	{
		h=1.0/power(n,-p);
	}
	return h;
}
int main()
{
	double i,j;
	int n;
	printf("请输入数字:");
	scanf("%lf",&i);
	printf("请输入幂:");
	scanf("%d",&n);
	j=power(i,n);
	printf("%lf",j);
}

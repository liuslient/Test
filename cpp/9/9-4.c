#include<stdio.h>
void pj(double n,double m)
{
	double i,j,h,k;
	i=1/n;
	j=1/m;
	h=(i+j)/2;
	k=1/h;
	printf("%.2lf",k);
}
int main()
{
	double n,m,g;
	printf("请输入两个数:\n");
	scanf("%lf %lf",&n,&m);
	pj(n,m);
}

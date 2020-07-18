#include<stdio.h>
int main()
{
	float n,m,t;
	scanf("%f %f",&n,&m);
	t=m/n;
	printf("At %.2f megabits per second,a file of %.2f megabytes downloads in %.2f seconds",n,m,t);
}

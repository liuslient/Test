#include<stdio.h>
void hu(double *n,double *m,double *i)
{
	double j;
	if(*n>*m)
	{
		j=*n;
		*n=*m;
		*m=j;
	}
	if(*n>*i)
        {
                j=*n;
                *n=*i;
                *i=j;
        }
	if(*m>*i)
        {
                j=*m;
                *m=*i;
                *i=j;
        }
}
int main()
{
	double a,b,c;
	printf("请输入三个数字:\n");
	scanf("%lf %lf %lf",&a,&b,&c);
	hu(&a,&b,&c);
	printf("%lf %lf %lf",a,b,c);
}

#include<stdio.h>
#include<stdlib.h>
double cha(double h[],int n);
double cha(double h[],int n)
{
	double max,min,k;
	int i;
	max=min=h[0];
	for(i=0;i<n;i++)
	{
		if(max<h[i])
		{
			max=h[i];
		}
		if(min>h[i])
		{
			min=h[i];
		}
	}
	k=max-min;
	return k;
}
int main()
{
	double m;
	double h[10]={1,2,3,4,5,6,7,8,9,10};
	m=cha(h,10);
	printf("%lf\n",m);
}

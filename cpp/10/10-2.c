#include<stdio.h>
#include<stdlib.h>
void copy_arr(double target[],double source[],int n);
void copy_arr(double target[],double source[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		target[i]=source[i];
	}
}
void copy_ptr(double *target,double *source,int n);
void copy_ptr(double *target,double *source,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		*(target+i)=*(source+i);
	}
}
void copy(double *target,double *source1,double *source2);
void copy(double *target,double *source1,double *source2)
{
	double *i;
	for(i=source1;i<source2;i++)
	{
		*target++=*i;
	}
}
int main()
{
	int i;
	double source[5] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
	double target1[5];
        double target2[5];
        double target3[5];
        copy_arr(target1, source, 5);
        copy_ptr(target2, source, 5);
        copy(target3, source, source+5);
	for(i=0;i<5;i++)
	{
		printf("%.3lf  ",target1[i]);
	}
	printf("\n");
	for(i=0;i<5;i++)
        {
                printf("%.3lf  ",target2[i]);
        }
        printf("\n");
	for(i=0;i<5;i++)
        {
                printf("%.3lf  ",target3[i]);
        }
        printf("\n");
}

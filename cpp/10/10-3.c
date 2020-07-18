#include<stdio.h>
#include<stdlib.h>
int bijiao(int *h,int n)
{
	int *i,j;
	i=*h;
	for(j=0;j<n;j++)
	{
		if(i<*(h+j))
		{
			i=*(h+j);
		}
	}
	return i;
}
int main()
{
	int k;
	int h[10]={1,2,3,4,5,6,7,8,9,10};
	k=bijiao(h,10);
	printf("%d\n",k);
}

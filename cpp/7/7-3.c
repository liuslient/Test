#include<stdio.h>
int main()
{
	int n,a=0,b=0,i=0,j=0;
	while(scanf("%d",&n))
	{
		if(n==0)
			break;
		if(n%2==0)
		{
			a++;
			i+=n;
		}
		else
		{
			b++;
			j+=n;
		}
	}
	printf("偶数%d平均%d奇数%d平均%d",a,i/a,b,j/b);
}

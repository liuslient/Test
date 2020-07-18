#include<stdio.h>
int han(int n,int m);
int han(int n,int m)
{
	int i,a,b,c;
	b=n;
	c=m;
	if(n<m)
	{
		i=n;
		n=m;
		m=i;
	}
	while(m!=0)
	{
		i=n%m;
		n=m;
		m=i;
	}
	a=n;
	return (b*c/a);
}
int main()
{
	int n,m,z,k,h;
	scanf("%d %d %d",&n,&m,&z);
	k=han(n,m);
	h=z/k;
	printf("%d\n",h);
}

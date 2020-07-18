#include<stdio.h>
#define n 60
int main()
{
	int f,m;
	float s;
	scanf("%d",&f);
	while(f>0)
	{
		s=f/n;
		m=f*n;
		printf("小时:%f 分钟:%d 秒数:%d\n",s,f,m);
		scanf("%d",&f);
	}
}

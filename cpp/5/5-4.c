#include<stdio.h>
int main()
{
	float n,h;
	int m;
	printf("Enter a height in centimeters:");
	scanf("%f",&n);
	while(n>=0)
	{
		m=n/30.48;
		h=(n-m*30.48)/2.54;
		printf("%.2fcm = %d feet, %.1f inches\n",n,m,h);
		printf("Enter a height in centimesters:");
		scanf("%f",&n);
	}
}

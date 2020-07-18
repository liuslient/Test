#include<stdio.h>
int main()
{
	char lets[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i,j;
	for(i=6;i>0;i--)
	{
		for(j=6;j>=i;j--)
			printf("%c",lets[j-1]);
		printf("\n");
	}
}

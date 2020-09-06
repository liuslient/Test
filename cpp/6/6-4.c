#include<stdio.h>
int main()
{
	int i,j,w=0;
	char h[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for(i=0;i<6;i++)
	{
		for(j=0;j<=i;j++)
		{
			printf("%c",h[w]);
			w++;
		}
		printf("\n");
	}
}

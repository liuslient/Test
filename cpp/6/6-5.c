#include<stdio.h>
int main()
{
	int j,i;
	char c,ch;
	scanf("%c",&c);
	for(j=0;j<=c-'A';j++)
	{
		for(i=c-'A';i>j;i--)
			printf(" ");
		for(ch='A';ch<('A'+j);ch++)
			printf("%c",ch);
		for(ch-2;ch>'A'-1;ch--)
			printf("%c",ch);
		printf("\n");
	}
}

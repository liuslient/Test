#include<iostream>
#include<cstring>
#include<math.h>
#include<string>
using namespace std;

bool isPrime(int x){
    if (x==1)
    {
        return 0;
    }
    for (int i = 2; i <= sqrt(x); i++)
    {
        if (x%i==0)
        {
            return 0;
        }   
    }
    return 1;
}
int daoxu(int n)
{
    int flag1=0,flag2=0;
    flag1=isPrime(n);
    int m,x=0;
    m=n;
    while (m!=0)
    {
        x=x*10+m%10;
        m=m/10;
    }
    flag2=isPrime(x);
    if(flag1==1&&flag2==1){
        return n;
    }else{
        return 0;
    }
    
}

int main()
{
	int m,n;
	scanf("%d%d",&m,&n);
	int i,flag=0;
	int a[n-m+1],k=0; 
	for(i=m;i<=n;i++){
		if(daoxu(i)!=0){
			flag=1;
			a[k++]=daoxu(i);
		}
	}
	for(i=0;i<k;i++){
		printf("%d",a[i]);
		if(i!=k-1){
			printf(",");
		}
	}
	if(flag==0){
		printf("No");
	}
	return 0;
}
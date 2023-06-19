#include<iostream>
using namespace std;
int main()
{
    int a,b,c,x,y,z,flag=1;;
    cin>>a>>b>>c;
    for ( x = 123; x <= 987; x++)
    {
        y=x/a*b;
        z=x/a*c;
        if(x%a!=0||y>=1000||z>=1000){
            continue;
        }
        if(x/100+x/10%10+x%10+
           y/100+y/10%10+y%10+
           z/100+z/10%10+z%10==45 &&
           (x/100)*(x/10%10)*(x%10)*
           (y/100)*(y/10%10)*(y%10)*
           (z/100)*(z/10%10)*(z%10)==362880
        ){
            flag=0;
            cout<<x<<" "<<y<<" "<<z<<endl;
        }
    }
    if(flag){
        cout<<"No!!!";
    }
    
  
}
#include <iostream>
#include <cstdio>
using namespace std;
 
int main() {
	int i, j, a, b, c, i2, i3, sum, bj = 0;
	int number[10] = {0};
	scanf("%d%d%d", &a, &b, &c);
	for (i = 123; i * 1.0 * c / a  <= 987; i++)//解决比例，范围优化 
	{
		sum = 0;//初始值一般归0；
		for (j = 1; j <= 9; j++)
			number[j] = 0;
		number[i % 10] = 1;
		number[i / 10 % 10] = 1;
		number[i / 100 ] = 1;
		i2 = i * 1.0 * b / a ;
		number[i2 % 10] = 1;
		number[i2 / 10 % 10] = 1;
		number[i2 / 100 ] = 1;
		i3 = i * 1.0 * c / a ;
		number[i3 % 10] = 1;
		number[i3 / 10 % 10] = 1;
		number[i3 / 100] = 1;
		for (j = 1; j <= 9; j++) {
			sum += number[j];
		}
		if (sum == 9) {
			printf("%d %d %d\n", i, i2, i3);
			bj = 1;//标记一下
		}
 
	}
	if (bj == 0)
		printf("No!!!");
	return 0;
}

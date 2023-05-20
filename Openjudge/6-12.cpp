#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int a[40];
int main(){
	int n,cnt=0;
	cin>>n;
	a[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=cnt;j++)
        {
			a[j]=a[j]*2;
			while(a[j] / 10 != 0)
            {
				int t=a[j] / 10;
				a[j]=a[j]%10;
				j++;
				a[j]=a[j]*2+t;
			}
			if(j >cnt) cnt=j;
		}
	}
	for(int i=cnt;i>=0;i--)
    {
		cout<<a[i];
	}
} 

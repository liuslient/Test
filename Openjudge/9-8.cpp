#include<iostream>
#include<iomanip>
#include<cmath> 
using namespace std;
int main(){
	int n,max_n=0,min_n=0;
	double max=0.0f,min=10000.0f;
	double a[300];
	double sum=0.0f,average=0.0f,error=0.0f,max_error=0.0f; 
	cin >> n;
	for(int i=0;i<n;i++){
		cin >> a[i];
		sum+=a[i];
		if(a[i]>max){
			max=a[i];
			max_n=i;
		}
		if(a[i]<min){
			min=a[i];
			min_n=i;
		}
	}
	average=(sum-max-min)/(n-2);
	for(int i=0;i<n;i++){
		if( i!=max_n && i!=min_n ){
			error=fabs(a[i]-average);
		}
		if(error>max_error){
			max_error=error;
		}
	}
	cout << fixed << setprecision(2) << average << " " << max_error << endl;
	return 0;
}


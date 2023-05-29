#include<bits/stdc++.h>
using namespace std;
int main()
{
	double L,C,SL,c; 
	scanf("%lf%lf%lf",&L,&C,&c);
	SL=(1+C*c)*L; 
	SL/=2; 
	L/=2; 
	double left=0,right=L;
	while(left+1e-7<=right) 
	{
		double mid=(left+right)/2,r,jd,SSL; 
		r=(L*L+mid*mid)/(2*mid); 
		jd=asin(L/r); 
		SSL=r*jd;
		if(SSL>SL) right=mid;
		else left=mid;
	}
	printf("%.3lf",left); 
	return 0;
}
/*
const double pi=acos(-1);
int main()
{
    double l1,n,c,l2,am,r1,r2;
    cin>>l1>>n>>c;
    l2=(1+n*c)*l1;
    double al=0,ar=pi;
    while(ar-al>1e-8){
        am=(al+ar)/2;
        r2=l2/am;
        r1=l1/(2*sin(am/2));
        if(r2>r1)
            al=am;
        else
            ar=am;
    }
    printf("%.3lf",l2/al*(1-cos(al/2)));

}
*/
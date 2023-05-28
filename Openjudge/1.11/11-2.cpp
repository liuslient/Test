#include<bits/stdc++.h>

using namespace std;
double f(double x){
    return pow(x,5)-15*pow(x,4)+85*pow(x,3)-225*pow(x,2)+274*x-121;
}
int main()
{
    double L=1.5,R=2.4;
    while(L+0.00000001<R){
        double mid=(L+R)/2;
        if(f(mid)>0){
            L=mid;
        }else{
            R=mid;
        }
    }
    printf("%.6lf",L);
}
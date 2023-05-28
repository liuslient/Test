#include<bits/stdc++.h>
using namespace std;
int n,f;
const double PI=acos(-1);
double v[100005],sum=0;
bool check(double x){
    int res=0;
    for (int i = 0; i < n; i++)
    {
        res+=floor(v[i]/x);
    }
    return res>=f;
    
}

int main()
{
   cin>>n>>f;
   f++;
   for (int i = 0; i < n; i++)
   {
        int r;
        cin>>r;
        v[i]=PI*r*r;
        sum+=v[i];
   }
   double L=0,R=sum/f;
   while(L+0.000001<R){
    double mid=(L+R)/2;
    if(check(mid)) L=mid;
    else R=mid;
   }
   printf("%.3lf",L);
   

    
}
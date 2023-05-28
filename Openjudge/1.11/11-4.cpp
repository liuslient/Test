#include<bits/stdc++.h>
using namespace std;
int n,k,a[100002];
long long sum=0;
bool check(int x){
    int res=0;
    for (int i = 0; i < n; i++)
    {
        res+=a[i]/x;
    }
    return res>=k;
    
}

int main()
{
    cin>>n>>k;
    for (int i = 0; i < n; i++)
    {
        double t;
        cin>>t;
        a[i]=100*t;
        sum+=a[i];
    }
    if(sum<k){
        cout<<"0.00";
        return 0;
    }
    int L=1,R=1e9;
    while(L<R){
        int mid=(L+R+1)/2;
        if(check(mid)) L=mid;
        else R=mid-1;
    }
    printf("%.2lf",L / 100.0);
    
}
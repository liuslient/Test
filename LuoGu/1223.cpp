#include<bits/stdc++.h>
using namespace std;
int n,a[1010];
long long sum;
int main()
{
    cin>>n;
    for (int i = 1; i <= n; i++)
    {
        cin>>a[i];
        a[i]=a[i]*1001+i;
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
        cout<<a[i]%1001<<" ";
    cout<<endl;
    for(int i=1;i<n;i++){
        sum+=a[i]/1001*(n-i);
    }
    printf("%.2lf",1.0*sum/n);
    
}
#include<bits/stdc++.h>
using namespace std;
int m,n,a[1000005];


int main()
{
    cin>>n;
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }
    cin>>m;
    sort(a,a+n);
    for (int i = 0; i < n; i++)
    {
        int L=i+1,R=n-1;
        while(L<=R){
            int mid=(L+R)/2;
            if(a[i]+a[mid]==m){
                cout<<a[i]<< " "<<a[mid];
                return  0;
            }else if(a[i]+a[mid]<m){
                L=mid+1;
            }else{
                R=mid-1;
            }
        }
    }
    cout<<"No";
    
    
}
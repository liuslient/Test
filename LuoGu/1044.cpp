#include<bits/stdc++.h>
using namespace std;

int main()
{
    int a[30]={0};
    int n;
    cin>>n;
    a[1]=1;
    a[0]=1;
    for (int i = 2;i <= n; i++)
    {
       for(int j=1;j<=i;j++){
        a[i]+=a[j-1]*a[i-j];
       } 
    }
    cout<<a[n];
    
}

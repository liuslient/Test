#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,a[1005],flag[1005]={0},nmax=-1;
    cin>>n;
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
        flag[a[i]]++;
    }
    nmax=flag[0];
    for (int i = 0; i < n; i++)
    {
        if(flag[i]>nmax){
            nmax=flag[i];
        }
    }
    for (int i = 0; i < n; i++)
    {
        if(flag[i]==nmax&&nmax>n/2){
            cout<<i;
            return 0;
        }
    }
    cout<<"no";
    
}
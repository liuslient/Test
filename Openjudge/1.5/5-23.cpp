#include<iostream>
using namespace std;

int main()
{
    int i,m,n,mem,ans=0;
    cin>>m>>n;

    for ( i = 1; i <= n; i++)
    {
        cin>>mem;
        if(mem>m)
            ans++;
        else
            m-=mem;

    }
    cout<<ans;
    
}
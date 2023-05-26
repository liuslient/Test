#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;

int main()
{
    int n,m,i,j,time=0,w[10000]={0},tap[100]={0};
    cin>>n>>m;
    for ( i = 0; i < n; i++)
    {
        cin>>w[i];
    }
    for ( i = 0; i < m; i++)
    {
        tap[i]=w[i];
    }
    while (i<n)
    {
        int sub=tap[0];
        for ( j = 1; j < m; j++)
        {
            sub=min(sub,tap[j]);
        }
        time+=sub;
        for ( j = 0; j < m; j++)
        {
            tap[j]-=sub;
            if (tap[j]==0)
            {
                tap[j]=w[i++];
            }
            
        } 
    }
    int left=0;
    for ( i = 0; i < m; i++)
    {
        left=max(left,tap[i]);
    }
    cout<<time+left;
    
    
     
    
}
#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;

int main()
{
    int m,n,i,k,l,d;
    cin>>m>>n>>k>>l>>d;
    int x[1001]={0},y[1001]={0};
    for ( i = 1; i <= d; i++)
    {
        int aa,ab,ba,bb;
        cin>>aa>>ab>>ba>>bb;
        if (aa==ba)
        {
            y[min(ab,bb)]++;
        }
        else
        {
            x[min(aa,ba)]++;
        }
        
    }
    while (k--)
    {
        int maxn=0,p;
        for ( i = 1; i <= m; i++)
        {
            if(maxn<x[i])
            {
                maxn=x[i];
                p=i;
            }
        }
        x[p]=-1;
        
    }

    while (l--)
    {
        int maxn=0,p;
        for ( i = 1; i <= m; i++)
        {
            if(maxn<y[i])
            {
                maxn=y[i];
                p=i;
            }
        }
        y[p]=-1;
        
    }
    
    for ( i = 1; i <= m; i++)
    {
        if (x[i]==-1)
        {
            cout<<i<<" ";
        }
        
    }
    cout<<endl;
    for ( i = 1; i <= n; i++)
    {
        if (y[i]==-1)
        {
            cout<<i<<" ";
        }
        
    }

    
    
    
}
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m,r,s,a[105][105],b[105][105],l,k;
    cin>>n>>m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin>>a[i][j];
        }
    }
    cin>>r>>s;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < s; j++)
        {
            cin>>b[i][j];
        }
    }
    int nmin=1e9,ni,nj;
    for (int i = 0; i < n-r+1; i++)
    {
        for (int j = 0; j < m-s+1; j++)
        {
            int sum=0;
            for (l = i; l < i+r; l++)
            {
                for (k = j; k < j+s; k++)
                {
                    sum+=(abs(a[l][k]-b[l-i][k-j]));
                }
                
            }
            if(sum<nmin)
            {
                nmin=sum;
                ni=i;
                nj=j;
            }
            
        }
        
    }
    for (int i = ni; i < ni+r; i++)
    {
        for (int j = nj; j < nj+s; j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    
    
    
}
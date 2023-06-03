#include<iostream>
#include<cstring>
#include<math.h>
#include<string>
using namespace std;


int main()
{
    int n;
    int sum[100005];
    int pi[100005];
    int s_tot=0;
    int nmax=999999999;
    int nmin=0;
    cin>>n;
    for (int i = 0; i < n; i++)
    {
        cin>>pi[i]>>sum[i];
        s_tot+=sum[i];
    }
    for (int i = 0; i < n; i++)
    {
        int f=0,s=0,sd;
        for (int j = (i+1)%n; j!=i; j=(j+1)%n)
        {
            s+=sum[(j-1+n)%n];
            sd = min(s_tot - s,s);
            f+=sd*pi[j];
        }
        if(f<nmax)
        {
            nmax=f;
            nmin=i;
        }
        
    }
    cout<<nmin<<","<<nmax;
    
    
}
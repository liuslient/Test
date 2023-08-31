#include<bits/stdc++.h>
using namespace std;
long long f[205][205],n,k;
int main()
{
    cin>>n>>k;
    for (int i = 1; i <= k; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if(j>i){
                f[i][j]=f[i-1][j-1]+f[i][j-i];
            }
            if(i==j){
                f[i][j]=1;
            }
        }
        
    }
    cout<<f[k][n];
    
}
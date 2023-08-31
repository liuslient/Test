#include<bits/stdc++.h>
using namespace std;
long long a[5005]={0,1},la=1;
int main()
{
    int n;
    cin>>n;
    for (int i = n+2; i <=2*n; i++)
    {
        for (int j = 1; j <= la; j++)
        {
            a[j]*=i;
        }
        for (int j = 1; j <= la; j++)
        {
            a[j+1]+=a[j]/10;
            a[j]%=10;
            if(a[la+1]>0){
                la++;
            }
        }
        
    }
    for (int i = 1; i <=n; i++)
    {
        for (int j = la; j >= 1; j--)
        {
            a[j-1]+=a[j]%i*10;
            a[j]/=i;
            if(a[la]==0)
                la--;
        }
    }
    for(int i=la;i>=1;i--){
        cout<<a[i];
    }
    
}
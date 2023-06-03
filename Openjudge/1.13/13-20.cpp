#include<iostream>
#include<cstring>
#include<math.h>
#include<string>
using namespace std;
int n;
int xu[10005][10005]; 
int ti_num[10005];
int main()
{
    cin>>n;
    for (int i = 1; i <= n; i++)
    {
        int m,k;
        cin>>m>>k;
        for (int j = 1; j <= k; j++)
        {
            int t;
            cin>>t;
            xu[t][m]=1;
            ti_num[t]++;
        }
        
    }
    int nmax=ti_num[1],num=1;
    for (int i = 2; i <= 100; i++)
    {
        if (nmax<ti_num[i])
        {
            nmax=ti_num[i];
            num=i;
        }
        
    }
    cout<<num<<endl;
    for (int i = 0; i <= 100; i++)
    {
        if(xu[num][i])
        {
            cout<<i<<" ";
        }
    }
    
    
    
}
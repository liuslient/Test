#include <iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
using namespace std;
int main()
{
    int i,j,n;
    cin>>n;
    string s;
    int sex[n+10];
    double tall[n+10];
    for ( i = 1; i <= n; i++)
    {
        cin>>s;
        if (s =="male")
        {
            sex[i]=1;
        }
        else
        {
            sex[i]=0;
        }
        cin>>tall[i];
        
    }
    for ( i = 1; i < n; i++)
    {
        for ( j = 1; j <= n-i;j++)
        {
            if (sex[j]==0 &&sex[j+1]==1 || sex[j]==1&&sex[j+1]==1&&tall[j]>tall[j+1] || sex[j]==0&&sex[j+1]==0&&tall[j]<tall[j+1])
            {
                swap(tall[j],tall[j+1]);
                swap(sex[j],sex[j+1]);
            }
            
        }
        
    }
    for ( i = 1; i <= n; i++)
    {
        cout<<fixed<<setprecision(2)<<tall[i]<<" ";
    }
    
    

    
}
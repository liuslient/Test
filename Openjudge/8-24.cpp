#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
    int n,i,j,x=1;
    int a[10][10]={0};
    cin>>n;
    for ( i = 0; i <= 2*n-2; i++)
    {
        for ( j = i; j >= 0; j--)
        {
            if (j<n&&i-j<n)
            {
                if (i%2!=0)
                {
                    a[i-j][j]=x++;
                }
                else
                {
                    a[j][i-j]=x++;
                }
                
            }
            
        }
        
    }
    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    
    
    
}
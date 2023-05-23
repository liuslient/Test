#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
    int n,a[50][50]={},si,sj;
    cin>>n;
    int i=1,j=n,k=1,len=2*n-1;
    while (k<=len*len)
    {
        a[i][j]=k++;
        if (i==1&&j==len)
        {
            i=2;
        }
        else if (i==1)
        {
            i=len;
            j++;
        }
        else if (j==len)
        {
            i--;
            j=1;
        }
        else
        {
            if(a[i-1][j+1]==0)
            {
                i--;
                j++;
            }
            else
            {
                i++;
            }
        }
    }
    for ( i = 1; i <=len; ++i)
    {
        for ( j = 1; j <= len; ++j)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
        
    }
    
    
}
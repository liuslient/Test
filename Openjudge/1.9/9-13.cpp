#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,i,j,max=0;
	cin>>n;
 
	int a[n+5]={0},b[n+10];
	for(i=0;i<n;i++)
	    cin>>a[i];
    for ( i = 0; i <n; i++)
    {
        for ( j = i+1; j < n; j++)
        {
            if (a[i]==a[j])
            {
                a[j]=0;
            }
            
        }
        
    }
    for ( i = 0; i < n; i++)
    {
        if (a[i]!=0)
        {
            cout<<a[i]<<" ";
        }
        
    }
    
	
}
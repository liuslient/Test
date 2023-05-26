/*
#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;


int main()
{
    int n,i,max=-1,j;
    cin>>n;
    int a[n+10],b[n+10]={0};
    for ( i = 0; i < n; i++)
    {
        cin>>a[i];
        if(a[i]>max)
        {
            max=a[i];
        }
    }
    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j <= max; j++)
        {
            if(a[i]==j)
            {
                b[j]++;
            }
        }
        
        
    }
    for ( i = 0; i <= max; i++)
    {
        cout<<b[i]<<endl;
    }
}
*/
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,max=0;
	cin>>n;
 
	int a[n+5]={0};
	for(int i=1;i<=n;i++)
	cin>>a[i];
 
	for(int i=1;i<=n;i++)
	{
		if(a[i]>max)
		max=a[i];
	}
 
	for(int i=0;i<=max;i++)
	{
		int sum=0;
		for(int j=1;j<=n;j++)
		{
			if(i==a[j])
			sum++;
		}
		cout<<sum<<endl;
	}
	return 0;
}
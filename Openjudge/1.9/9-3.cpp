#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int main()
{
    int n,x,i;
    int a[10],b[10],c[10],flag=0;
    bool an[10]={0};
    for ( i = 1; i <= 7; i++)
    {
        cin>>a[i]>>b[i];
        c[i]=a[i]+b[i];
    }
    for ( i = 1; i <= 7; i++)
    {
        if (c[i]>8)
        {
            an[i]=1;
            flag++;
            
        }
        
    }
    if (flag>1)
    {
        for ( i = 1; i <=7; i++)
        {
            if (an[i]==1)
            {
                cout<<i;
                return 0;
            }
            
        }
        
    }
    else if(flag==1)
    {
        for ( i = 1; i <=7; i++)
        {
            if (an[i]==1)
            {
                cout<<i;
                return 0;
            }
            
        }
    }
    else
        cout<<0;
    
    
    
    
    
    
    
}
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{	
    int k,i,a[40],lc,x,flag=0;
    string c;
    cin>>c;
    lc=c.length();
    for ( i = 0; i < lc; i++)
    {
        a[i]=c[i]-'0';
    }
    for ( k = 2; k <= 9; k++)
    {
        x=0;
        for ( i = 0; i < lc; i++)
        {
            x=x*10+a[i];
            x=x%k;
        }
        if (x==0)
        {
            flag=1;
            cout<<k<<" ";
        }
        
        
    }
    if (flag==0)
    {
        cout<<"none";
    }
    
    

    
} 

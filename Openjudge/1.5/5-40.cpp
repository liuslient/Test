#include<iostream>
using namespace std;
int main()
{
    int n,x,i,ans=0,sum=0;
    cin>>n;
    for ( i = 1; i <= n; i++)
    {
        ans=0;
        x=i;
        while (x>0)
        {
            if (x%10==1)
            {
                ans++;
            } 
            x/=10;
        }   
        sum+=ans;
    }  
    cout<<sum;
}
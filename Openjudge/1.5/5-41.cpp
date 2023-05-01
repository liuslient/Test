#include<iostream>
using namespace std;
int main()
{
    int l,r,x,i,ans=0,sum=0;
    cin>>l>>r;
    for ( i = l; i <= r; i++)
    {
        ans=0;
        x=i;
        while (x>0)
        {
            if (x%10==2)
            {
                ans++;
            } 
            x/=10;
        }   
        sum+=ans;
    }  
    cout<<sum;
}
#include<iostream>
using namespace std;

int main()
{
    int i,n,shou_ya,shu_ya,ans=0,max=0;
    cin>>n;
    for ( i = 0; i < n; i++)
    {
        cin>>shou_ya>>shu_ya;
        if ((shou_ya>89&&shou_ya<141)&&(shu_ya>59&&shu_ya<91))
        {
            ans++;
            if (ans>max)
            {
                max=ans;
            }
        }
        else
        { 
            ans=0;
        }
        
    }
    
    cout<<max;
    
}
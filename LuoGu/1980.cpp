#include<iostream>
using namespace std;
int main()
{
    int n,x,flag=0,h;
    cin>>n>>x;
    for (int i = 1; i <= n; i++)
    {
        h=i;
        while (h>0)
        {  
            if(h%10==x)
            {
                flag++;
            }
            h/=10;
        }
        
    }
    cout<<flag;
    
    
}


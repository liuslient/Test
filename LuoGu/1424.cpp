#include<iostream>
using namespace std;
int main()
{
    int x,n,day=0;
    cin>>x>>n;
    for (int i = 0; i < n; i++)
    {
        if((x+i)%7==6||(x+i)%7==0)
        {
            day++;
        }
    }
    cout<<(n-day)*250;
    
    
}


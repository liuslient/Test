#include<iostream>
using namespace std;

int main()
{
    int m,k,i,count=0;
    cin>>m>>k;
    i=m;
    while (m>0)
    {
        if (m%10==3)
        {
            count++;
        }
        m/=10;
        
    }
    
    if(i%19==0&&count==k)
    {
        cout<<"YES";
    }
    else
        cout<<"NO";
}
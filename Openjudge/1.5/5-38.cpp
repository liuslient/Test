#include<iostream>
using namespace std;
int main()
{
    int n,c,ans,i;
    cin>>n;
    if(n==0)
        cout<<0;
    for ( i = n; i > 0; i--)
    {
        cin>>c;
        if (n==1)
        {
            cout<<0;
        }
        else
        {
            cout<<c*i<<" ";
        }
        
    }
    
}
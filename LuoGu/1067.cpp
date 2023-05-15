#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;

int main()
{
    int n,i,x,y,a;
    cin>>n;
    for ( i =n; i >= 0; i--)
    {
        cin>>a;
        if(a==0)
        {
            continue;
        }
            
        if (a>0&&i<n)
        {
            cout<<"+";
        }
        if (a!=1&&a!=-1||i==0)
        {
            cout<<a;
        }
        if(a==-1&&i>0)
            cout<<"-";
        if(i>1)
            cout<<"x^"<<i;
        if(i==1)
        cout<<"x";

        
        
    }
}
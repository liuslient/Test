#include<iostream>
using namespace std;
int main()
{
    int i,gao,kuan,sta,j;
    char fu;
    cin>>gao>>kuan>>fu>>sta;
    if(sta)
    {
        for ( i = 1; i <= gao; i++)
        {
            for ( j = 1; j <= kuan; j++)
            {
                cout<<fu;
            }
            cout<<endl;
        
        }
    }
    else
    {
        for ( i = 1; i <= kuan; i++)
            cout<<fu;
        cout<<endl;

        for ( i = 2; i <= gao-1; i++)
        {
            cout<<fu;
            for ( j = 1; j <= kuan-2; j++)
            {
                cout<<" ";
            }
            cout<<fu;
            cout<<endl;
            
        }



        for ( i = 1; i <= kuan; i++)
            cout<<fu;
        cout<<endl;
        
    }
    
}
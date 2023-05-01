#include<iostream>
#include<string>
using namespace std;
int main()
{
    int r,c,i,j,sum=0,at=0;
    cin>>r>>c;
    int a[r+10][c+10];
    for ( i = 1; i <= r; i++)
    {
        for ( j = 1; j<=c; j++)
        {
            cin>>a[i][j];
            sum+=a[i][j];
        }
        
    }
    for ( i = 2; i < r; i++)
    {
        for ( j = 2; j<c; j++)
        {
            cin>>a[i][j];
            at+=a[i][j];
        }
        
    }
    cout<<sum-at;

    
}
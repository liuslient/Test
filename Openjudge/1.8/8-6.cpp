#include <iostream>
#include<iomanip>
using namespace std;
int main()
{
    int r,c, i, j,ans=0;
    double s;
    cin>>r>>c;
    int a[r+10][c+10];
    int b[r+10][c+10];
    for ( i = 1; i <=r; i++)
    {
        for ( j = 1; j<=c; j++)
        {
            cin>>a[i][j];
        }
    }
    for ( i = 1; i <=r; i++)
    {
        for ( j = 1; j<=c; j++)
        {
            cin>>b[i][j];
        }
    }
    for ( i = 1; i <=r; i++)
    {
        for ( j = 1; j<=c; j++)
        {
            if(a[i][j]==b[i][j])
                ans++;
        }
    }
    cout<<fixed<<setprecision(2)<<100.0*ans/r/c;
}
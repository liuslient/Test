#include<iostream>
#include<string>
using namespace std;
int main()
{
    int a[5][5],i,j,n,m;
    for ( i = 0; i < 5; i++)
    {
        for ( j = 0; j < 5; j++)
        {
            cin>>a[i][j];
        }
    }
    cin>>n>>m;
    for ( i = 0; i < 5; i++)
    {
        swap(a[n-1][i],a[m-1][i]);
    }
    for ( i = 0; i < 5; i++)
    {
        for ( j = 0; j < 5; j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }

}
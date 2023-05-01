#include<iostream>
#include<string>
using namespace std;
int main()
{
    int n,i,j;
    int a[5][5];
    for ( i = 0; i < 5; i++)
    {
        for ( j = 0; j<5; j++)
        {
            cin>>a[i][j];
        }
    }
    int r[5],c[5];
    for ( i = 0; i < 5; i++)
    {
        int big=0;
        for ( j = 0; j<5; j++)
        {
            if(big<a[i][j])
            {
                big=a[i][j];
                r[i]=j;
            }
        }
    }
    for ( i = 0; i < 5; i++)
    {
        int small=999999999;
        for ( j = 0; j<5; j++)
        {
            if(small<a[j][i])
            {
                small=a[j][i];
                c[i]=j;
            }
        }
    }
    for ( i = 0; i < 5; i++)
    {
        if(c[r[i]]==i)
        {
            cout<<i+1<<" "<<r[i]+1<<" "<<a[i][r[i]];
            printf("dusafgb\n");
            return 0;
        }
    }
    cout<<"not found";
    
    
}
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
//每次打印的次对角线上的行列下标之和是从0开始到（row+col-2
int a[10001][10001]={0};
int main()
{
    int row,col,i,j,k;
    cin>>row>>col;
    int a[row+10][col+10];
    for ( i = 0; i < row; i++)
    {
        for ( j = 0; j < col; j++)
        {
            cin>>a[i][j];
        }
    }
    for ( i = 0; i < row+col-1; i++)
    {
        for ( j = 0; j < row; j++)
        {
            for ( k = 0; k < col; k++)
            {
                if(k+j==i)
                    cout<<a[j][k]<<endl;
            }
            
        }
        
    }
    
}
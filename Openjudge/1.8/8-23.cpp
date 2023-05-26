#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
    int row,col,i,j,k,size,dir=0,x,y;
    cin>>row>>col;
    size=row*col;
    int a[row+10][col+10],b[row+10][col+10]={0};
    int step[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
    for ( i = 0; i < row; i++)
    {
        for ( j = 0; j < col; j++)
        {
            cin>>a[i][j];
        }
    }
    i=j=0;
    for ( k = 0; k < size; k++)
    {
        cout<<a[i][j]<<endl;
        b[i][j]=1;
        x=i+step[dir][0];
        y=j+step[dir][1];
        if(x<0||x>=row||y<0||y>=col||b[x][y])
            dir=(dir+1)%4;
        i+=step[dir][0];
        j+=step[dir][1];
    }
    
    
    
}
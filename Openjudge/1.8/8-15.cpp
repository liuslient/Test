#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
    int n,m,i,j,flag=0;
    cin>>m>>n;
    int a[10][10]={0},b[10][10]={0};
    a[5][5]=m;
    for (int day = 1; day <= n; day++)
    {
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 1; j <= 9; j++)
            {
                if (a[i][j]!=0)
                {
                    for (int ii = i-1; ii <= i+1; ii++)
                    {
                        for (int jj = j-1; jj <= j+1; jj++)
                        {
                            if (i==ii&&jj==j)
                            {
                                b[ii][jj]+=2*a[i][j];
                            }
                            else
                            {
                                b[ii][jj]+=a[i][j];
                            }
                            
                        }
                        
                    }
                    
                }
                
            }
            
        }

        for (int i = 1; i <= 9; i++)
        {
            for (int j = 1; j <= 9; j++)
            {
                a[i][j]=b[i][j];
                b[i][j]=0;
            }
            
        }
        
        
    }
    for ( int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    
    
    

    
}
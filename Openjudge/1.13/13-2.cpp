#include<iostream>
#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;

int main()
{
    int a,rq[13][32]={0},w[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    cin>>a;
    for (int i = 1; i <= 12; i++)
    {
        for (int j = 1; j <= w[i]; j++)
        {
            rq[i][j]=a;
            ++a;
            if(a==8)
            a=1;
            if (j==13&&rq[i][j]==5)
            {
                cout<<i<<endl;
            }
            
        }
        
    }
    
}
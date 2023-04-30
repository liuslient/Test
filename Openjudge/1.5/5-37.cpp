#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

int main()
{
    int M,N,X,m=0,i;
    cin>>M>>N>>X;
    while (X>0)
    {
        m+=N;
        if (m>=M)
        {
            N+=M/N;
            m=0;
        }
        X--;
        
    }
    cout<<N;
    
    
}
#include<iostream>
using namespace std;

int main()
{
    int i,jj=0,mm=0,x;
    for ( i = 1; i <= 12; i++)
    {
        jj+=300;
        cin>>x;
        jj-=x;
        if(jj<0)
        {
            cout<<"-"<<i;
            return 0;
        }
        mm+=jj/100*100;
        jj%=100;
    }
    cout<<jj+mm*1.2;
    
}
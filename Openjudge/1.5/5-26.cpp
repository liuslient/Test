#include<iostream>
using namespace std;

int main()
{
    int i,n,a,count=0,ge,shi,bai,qian;
    cin>>n;
    for ( i = 0; i < n; i++)
    {
        cin>>a;
        ge=a%10;
        qian=a/1000;
        bai=a/100%10;
        shi=a/10%10;
        if(ge-qian-bai-shi>0)
            count++;
    }
    cout<<count;
    
}
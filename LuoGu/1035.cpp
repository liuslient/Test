#include<iostream>
using namespace std;
int main()
{
    int k,n;
    double sum=0;
    cin>>k;
    for (int i = 1; ; i++)
    {
        sum+=1/double(i);
        if(sum>k)
        {
            cout<<i;
            return 0;
        }
    }
    
}


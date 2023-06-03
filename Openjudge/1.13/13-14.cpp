#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
bool judge(int m)
{
    double x=sqrt(m);
    if(floor(x)==x)
    {
        return true;
    }
    return false;
}
int main()
{
    int n;
    cin>>n;
    int count=0;
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            for (int k = 0; k <= 9; k++)
            {
                int flag1=0,flag2=0;
                if(i==j||j==k||k==i)
                {
                    flag1=1;
                }
                int s=i*100+j*10+k;
                if(judge(s))
                {
                    flag2=1;
                }
                if(flag1==1&&flag2==1)
                {
                    count++;
                    if(n==count)
                    {
                        cout<<s<<endl;
                    }
                }
            }
            
        }
        
    }
    
}
#include <iostream>
using namespace std;

int main()
{
    int a,b,c,d,sum,time_1=0,time_2=0;
    cin>>a>>b>>c>>d;
    for (int i = 0; i < a; i++)
    {
        time_1+=60;
    }
    time_1+=b;
    for (int i = 0; i < c; i++)
    {
        time_2+=60;
    }
    time_2+=d;
    sum=time_2-time_1;
    int s,f;
    s=sum/60;
    f=sum%60;
    cout<<s<<" "<<f;
}

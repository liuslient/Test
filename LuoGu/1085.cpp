#include<iostream>
#include <iomanip>
using namespace std;
int main()
{
    int x,y,ans=0,day=1,maxn=8;
    for (int i = 1; i <= 7; i++)
    {
        cin>>x>>y;
        if(x+y>maxn){
            maxn=x+y;
            ans=day;
        }
        day++;
    }
    cout<<ans;
    
    
}


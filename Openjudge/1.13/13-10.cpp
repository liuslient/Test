#include<bits/stdc++.h>
using namespace std;
bool isPrim(int n){
    for (int i = 2; i <=sqrt(n); i++)
    {
        if(n%i==0){
            return false;
        }
    }
    return true;
    
}
int main()
{
    int x,y,ans=0;
    cin>>x>>y;
    if(x>y)
    {
        swap(x,y);
    }
    x=max(2,x);
    for (int i = x; i <= y; i++)
    {
        if(isPrim(i))
        {
            ans++;
        }
    }
    cout<<ans;
    
    
}
#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    int n,s,a,b;
    cin>>n>>s;
    cin>>a>>b;
    int x[n+10],y[n+10],v[n+10]={0};
    for (int i = 1; i <= n; i++)
    {
        cin>>x[i]>>y[i];
    }
    int cnt=0;
    for (int i = 1; i <= n; i++)
    {
        int minn=1e9;
        int p;
        for (int j = 1; j <= n; j++)
        {
            if(x[j]<=a+b&&v[j]==0&&y[j]<minn){
                minn=y[j];
                p=j;
            }
        }
        if(s>=minn){
            s-=minn;
            cnt++;
        }else{
            cout<<cnt;
            return 0;
        }
        
        v[p]=1;
        
    }
    cout<<0;
    
    
}
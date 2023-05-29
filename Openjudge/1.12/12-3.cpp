#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,i,flag=0;
    string name[1000];
    float tem[1000];
    bool ke[1000];
    bool ll[1000]={0};
    cin>>n;
    for ( i = 1; i <= n; i++)
    {
        cin>>name[i]>>tem[i]>>ke[i];
        if(tem[i]>=37.5 && ke[i]==1)
        {
            ll[i]=1;
            flag++;
        }
    }
    for ( i = 1; i <= n; i++)
    {
        if(ll[i]==1)
        {
            cout<<name[i]<<endl;
        }
    }
    
    cout<<flag;
    
    
}
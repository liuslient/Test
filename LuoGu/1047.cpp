#include<iostream>
using namespace std;
int main()
{
    int l,m;
    cin>>l>>m;
    int u[m+10],v[m+10];
    for (int i = 0; i < m; i++)
    {
        cin>>u[i]>>v[i];
    }
    int flag[l+10];
    for (int i = 0; i <=l ; i++)
    {
        flag[i]=1;
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = u[i]; j <= v[i]; j++)
        {
            flag[j]=0;
        }
        
    }
    int cnt=0;
    for (int i = 0; i <= l; i++)
    {
        if(flag[i]==1){
            cnt++;
        }
    }
    cout<<cnt;
    
    
    
    
    
}

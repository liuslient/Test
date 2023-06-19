#include<bits/stdc++.h>
using namespace std;
int n;
bool cis[20];
int a[29];

void pr(){
    for (int i = 1; i <= n; i++)
    {
        cout<<setw(5)<<a[i];
    }
    cout<<endl;
    
}
void dfs(int x){
    if(x>n){
        pr();
    }
    for (int i = 1; i <= n; i++)
    {
        if(!cis[i]){
            a[x]=i;
            cis[i]=1;
            dfs(x+1);
            cis[i]=0;
        }
    }
    
}


int main()
{
    
    cin>>n;
    dfs(1);
}
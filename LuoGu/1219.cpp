#include<bits/stdc++.h>
using namespace std;
int n,cnt;
bool lie[20];//列
bool u[40];//左上到右下
bool v[40];//右上到左下
int a[20];

void pr(){
    if(cnt<=3){
        for (int i = 1; i <= n; i++)
        {
            cout<<a[i]<<" ";
        }
        cout<<endl;
    }
}

void  dfs(int x){
    if(x>n){
        cnt++;
        pr();
        
        return ;
    }
    for (int i = 1; i <=n; i++)
    {
        if(!lie[i]&&!u[x-i+n]&&!v[x+i]){
            lie[i]=1;
            u[x-i+n]=1;
            v[x+i]=1;
            a[x]=i;
            dfs(x+1);
            lie[i]=0;
            u[x-i+n]=0;
            v[x+i]=0;
        }
    }
    
}

int main()
{
    cin>>n;
    dfs(1);
    cout<<cnt;
    return 0;
}
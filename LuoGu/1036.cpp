#include <iostream>
#include <cstring>
using namespace std;
int n,k,cnt=0;
int a[30];
bool isPrime(int x){
    if(x<=1){
        return 0;
    }
    for (int i = 2; i*i <= x; i++)
    {
        if(x%i==0){
            return 0;
        }
    }
    return 1;
}

void dfs(int p,int x,int s)
{
    if(x==k){
        if(isPrime(s))
            cnt++;
        return ;
    }
    if(p>n){
        return ;
    }
    dfs(p+1,x+1,s+a[p]);//选p
    dfs(p+1,x,s);//不选p

}

int main()
{
    cin>>n>>k;
    for (int i = 1; i <= n; i++)
    {
        cin>>a[i];
    }
    dfs(1,0,0);
    cout<<cnt;
    
}
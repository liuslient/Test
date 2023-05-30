#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[105][105];
void shangxia(){
    for (int i = 0; i < n/2; i++)
    {
        for (int j = 0; j < m; j++)
        {
            swap(a[i][j],a[n-i-1][j]);
        }
    }
}
void zuoyou(){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m/2; j++)
        {
            swap(a[i][j],a[i][m-1-j]);
        }
    }
}
void zhuanzhi(){
    for (int i = 0; i < max(n,m); i++)
    {
        for (int j = 0; j <= i; j++)
        {
            swap(a[i][j],a[j][i]);
        }
        
    }
    swap(n,m);
    
}
int main()
{
    cin>>n>>m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin>>a[i][j];
        }
        
    }
    string op;
    cin>>op;
    for (int i = 0; i < op.size(); i++)
    {
        if(op[i]=='A')
        {
            zhuanzhi();
            zuoyou();
        }else if(op[i]=='B'){
            
            zhuanzhi();
            shangxia();
        }else if(op[i]=='C'){
            zuoyou();
        }else{
            shangxia();
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
        
    }
    
    
}
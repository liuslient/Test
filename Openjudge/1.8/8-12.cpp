#include<iostream>
#include<cstdio>
using namespace std;
char a[11][11];
char b[11][11];
bool x[6];
int main() {
    int n,i,j;
    cin>>n;
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= n; j++)
        {
            cin>>a[i][j];
        }
        
    }
    for ( i = 1; i <= n; i++)
    {
        for ( j = 1; j <= n; j++)
        {
            cin>>b[i][j];
        }
        
    }
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++) {
            if(a[i][j]!=b[j][n-i+1])x[1]=1;
            if(a[i][j]!=b[n-j+1][i])x[2]=1;
            if(a[i][j]!=b[n-i+1][n-j+1])x[3]=1;
            if(a[i][j]!=b[i][j])x[4]=1;
        }
    for(int i=1; i<=4; i++) {
        if(x[i]==0) {
            cout<<i;
            x[6]=1;
        }

    }
    if(x[6]==0)cout<<"5";
    return 0;
}
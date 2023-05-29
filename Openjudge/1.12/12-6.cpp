#include<bits/stdc++.h>
using namespace std;
int n,m,str;
struct  room{
    int flag;
    int num;
    int sum;
}a[10005][105];

int main()
{
    cin>>n>>m;
    for (int i = 1; i <= n; i++)
    {
        int p=0;
        for (int j = 0; j < m; j++)
        {
            cin>>a[i][j].flag>>a[i][j].num;
            if(a[i][j].flag==1)
                p++;
        }
        a[i][m].sum=p;
    }
    cin>>str;
    int ans=0;
    int pre=1;
    int x=str;
    while (pre<=n)
    {
        int s=0,j;
        ans=(ans+a[pre][x].num)%20123;
        a[pre][x].num=(a[pre][x].num-1)%a[pre][m].sum+1;
        for (j = x;; j++)
        {
            if (j==m)
                j=0;
            if(a[pre][j].flag==1)//有楼梯
                s++;
            if(s==a[pre][x].num)
                break;
            
        }
        pre++;
        x=j;
        
    }
    cout<<ans;  
}
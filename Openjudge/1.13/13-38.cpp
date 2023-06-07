#include<iostream>
#include<stdio.h>
#include<string.h>
#include<cmath>
#include<algorithm>

using namespace std;
int m,n,k,p,cnt;
struct node
{
    int x,y,s;
} a[401];
bool cmp(node a,node b){
    return a.s>b.s;
}
int main()
{
    cin>>m>>n>>k;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin>>p;
            if(p>0){
                cnt++;
                a[cnt].x=i;
                a[cnt].y=j;
                a[cnt].s=p;
            }
        }
    }
    sort(a+1,a+cnt+1,cmp);
    int st=0,xi=0,yi=a[1].y,sum=0;
    for (int i = 1; i <= cnt; i++)
    {
        if(st+abs(xi-a[i].x)+abs(yi-a[i].y)+1+a[i].x>k){
            cout<<sum;
            return 0;
        }
        st+=abs(xi-a[i].x)+abs(yi-a[i].y)+1;
        xi=a[i].x;
        yi=a[i].y;
        sum+=a[i].s;
    }
    cout<<sum;
    
}
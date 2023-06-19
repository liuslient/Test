/*
#include<bits/stdc++.h>
using namespace std;

int n,c[4][30],v[30],a[30];

void dfs(int x,int y,int t){
    for (int i = 1; i <= n; i++)
    {
        if(a[c[1][i]]>=0&&a[c[2][i]]>=0&&a[c[3][i]>=0]){
            if((a[c[1][i]]+a[c[2][i]])%n!=a[c[3][i]]&&(a[c[1][i]]+a[c[2][i]]+1)%n!=a[c[3][i]])
                return ;
        }
    }
    
    if(y>n){
        if(t==0){
            for (int i = 0; i < n; i++){
                cout<<a[i]<<" ";
            }
        }
        return ;   
    }
    int z=c[x][y];
    if(x<=2){
        if(a[z]!=-1){
            dfs(x+1,y,t);
        }
        else{
            for (int i = 0; i < n; i++){
                if(!v[i]){
                    v[i]=1;
                    a[z]=i;
                    dfs(x+1,y,t);
                    v[i]=0;
                    a[z]=-1;
                }
            }
            
        }
    }
    else if(y==3){
        t+=a[c[1][y]]+a[c[2][y]];
        if(a[z]==t%n){
            dfs(1,y+1,t/n);
        }
        if(a[z]==-1&&v[t%n]==0){
            a[z]=t%n;
            v[t%n]=1;
            dfs(1,y+1,t/n);
            a[z]=-1;
            v[t%n]=0;
        }
    }
}

int main()
{
    memset(a,-1,sizeof(a));
    cin>>n;
    for (int i = 1; i <= 3; i++)
    {
        for (int j = n; j >= 1; j--)
        {
            char t;
            cin>>t;
            c[i][j]=t-'A';
        }
        
    }
    dfs(1,1,0);
    return 0;
    
}
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int n;
int vis[30], a[30]; //a 用来记住字母代表的数字 
int v[4][30];    // 保存字母

void dfs(int y, int x, int t)
{
	for (int i = 1; i <= n; i++)        //提前预测判断，免得再递归，减少时间 
	{
		if (a[v[1][i]] != -1 && a[v[2][i]] != -1 && a[v[3][i]] != -1)
		{
			if (a[v[3][i]] != (a[v[1][i]] + a[v[2][i]]) % n && a[v[3][i]] != (a[v[2][i]] + a[v[1][i]] + 1) % n)
			{
				return;
			}
		}
	}

	if (x > n)
	{
		for (int i = 0; i < n; i++)
		{
			cout << a[i] << " ";
		}
		return;
	}
	
	int m = v[y][x];
	if (y <= 2)
	{
		if (a[m] != -1)
		{
			dfs(y + 1, x, t);
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				if (vis[i] == 0)
				{
					a[m] = i;
					vis[i] = 1;
					dfs(y + 1, x, t);
					a[m] = -1;
					vis[i] = 0;
				}
			}
		}
	}
	else if (y == 3)
	{
		t += a[v[y - 1][x]] + a[v[y - 2][x]];
		if (a[m] != -1)
		{
			if (a[m] == t % n)     
			{
				dfs(1, x + 1, t / n); 
			}
		}
		else
		{
			if (a[m] == -1 && vis[t % n] == 0)
			{
				a[m] = t % n;
				vis[t % n] = 1;
				dfs(1, x + 1, t / n); 
				a[m] = -1;
				vis[t % n] = 0;
			}
		}
	}
}

int main()
{
	cin >> n;
	memset(a, -1, sizeof(a));  
	for (int i = 1; i <= 3; i++)
	{
		for (int j = n; j >= 1; j--)
		{
			char m;
			cin >> m;
			v[i][j] = m - 'A';  
		}
	}
	dfs(1, 1, 0);
	return 0;
}

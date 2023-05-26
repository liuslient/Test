#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;

int main()
{
    int n,a[35][105],nmax=-1,len[35];
    cin>>n;
    for (int i = 1; i <= n; i++)
    {
        char ch;
        int idx=0;
        scanf("%d%c",&a[i][idx++],&ch);
        while(ch==',')
        {
            if (a[i][idx-1]>nmax)
            {
                nmax=a[i][idx-1];
            }
            scanf("%d%c",&a[i][idx++],&ch);
            
        }
        len[i]=idx;
    }
    cout<<nmax<<endl;
    int cnt=0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < len[i]; j++)
        {
            if(a[i][j]==nmax)
            {
                if (cnt==0)
                {
                    cout<<i;
                    cnt++;
                }
                else
                {
                    cout<<","<<i;
                }
                break;
            }
        }
        
    }
    
    
}
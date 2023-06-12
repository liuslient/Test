#include<iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[n+10];
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
    }
    int cnt=0;
    for (int k=0; k < n; k++)
    {
        int flag=0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i+1; j < n; j++)
            {
                if(a[i]+a[j]==a[k]){
                    flag=1;
                }
            }
        }  
        cnt+=flag;
    }
    cout<<cnt;
    
}

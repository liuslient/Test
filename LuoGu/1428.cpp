#include<iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[n+10],b[n+10]={0};
    for (int i = 1; i <= n; i++)
    {
        cin>>a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        int cnt=0;
        for (int j = 1; j < i; j++)
        {
            if(a[i]>a[j]){
                cnt++;
            }
        }
        cout<<cnt<<" ";
        
    }
    
    
    

    
}

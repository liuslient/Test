#include<iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[n+10];
    for (int i = 1; i <= n; i++)
    {
        cin>>a[i];
    }
    int cnt=0,max=-1;;
    a[0]=-1;
    for (int i = 1; i <= n; i++)
    {
        if(a[i]>a[i-1]){
            cnt++;
            if(max<cnt){
                max=cnt;
            }
        }else{
            cnt=1;
        }
        
    }
    cout<<max;
    
}

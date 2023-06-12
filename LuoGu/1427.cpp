#include<iostream>
using namespace std;
int main()
{
    int a[105],x,n=0;
    cin>>x;
    while(x!=0){
        a[++n]=x;
        cin>>x;
    }
    for (int i = n; i >= 1; i--)
    {
        cout<<a[i]<<" ";
    }
    

    
}

#include<bits/stdc++.h>
using namespace std;
int zhuan(int n){
    int count=0;
    while (n)
    {
        if(n%2==1){
            count++;
        }
        n/=2;
    }
    return count;
    
}

int main()
{
    int n,l;
    cin>>n;
    l=zhuan(n);
    cout<<l;

    
    
    
}
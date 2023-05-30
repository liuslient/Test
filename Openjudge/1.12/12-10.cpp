#include<bits/stdc++.h>
using namespace std;
bool isPrime(int x){
    for (int i = 2; i*i <=x; i++)
    {
        if(x%i==0) return 0;
    }
    return 1;
    
}

int main()
{
    int n,cnt=0;
    cin>>n;
    for (int i = 3; i+2 <=n; i++)
    {
        if(isPrime(i)&&isPrime(i+2)){
            cout<<i<<" "<<i+2<<endl;
            cnt++;
        }
    }
    if(!cnt) cout<<"empty";
    
    
}
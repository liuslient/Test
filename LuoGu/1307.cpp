#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;

int main()
{
    int n;
    cin>>n;
    if(n==0){
        cout<<0;
        return 0;
    }
    if(n<0){
        cout<<'-';
        n=-n;
    }
    while(n%10==0){
        n/=10;
    }
    while(n){
        cout<<n%10;
        n/=10;
    }

    
}
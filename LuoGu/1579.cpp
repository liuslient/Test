#include <iostream>
#include <cstring>
using namespace std;

bool isPrime(int x){
    if(x<=1){
        return 0;
    }
    for (int i = 2; i*i <= x; i++)
    {
        if(x%i==0){
            return 0;
        }
    }
    return 1;
    
}
int main()
{
    int n;
    int a,b,c;
    cin>>n;
    for (int i = 2; i < n; i++)
    {
        if(isPrime(i)){
            for (int j = 2; j < n; j++)
            {
                if(isPrime(j)&&isPrime(n-i-j)){
                    cout<<i<<" "<<j<<" "<<n-i-j;
                    return 0;
                }
            }
            
        }
    }
    
}
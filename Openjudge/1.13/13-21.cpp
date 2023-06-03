#include<iostream>
#include<cstring>
#include<math.h>
#include<string>
using namespace std;

bool isPrime(int x){
    for (int i = 2; i <= sqrt(x); i++)
    {
        if (x%i==0)
        {
            return 0;
        }
        
    }
    return 1;
    
}
int get(int x){
    if(isPrime(x)) return x;
    for (int i = x/2; i >= 2; i--)
    {
        if(x%i==0&&isPrime(i)) return i;
    }
    
}


int main()
{
   int n,m;
   cin>>n>>m;
   for (int i = n; i < m; i++)
   {
        cout<<get(i)<<",";
   }
   cout<<get(m);
   
    
}
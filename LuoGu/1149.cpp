#include <iostream>
#include <cstring>
using namespace std;

int m[10]={6,2,5,5,4,5,6,3,7,6};

int f(int x){
    int sum=0;
    if(x==0)
        return 6;
    while (x>0)
    {
        sum+=m[x%10];
        x/=10;
    }
    return sum;
    
}
int main()
{
    int n,cnt=0;
    cin>>n;
    for (int i = 0; i <= 999; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            if(f(i)+f(j)+2+2+f(i+j)==n){
                cnt++;
            }
        }
        
    }
    cout<<cnt;
    
}
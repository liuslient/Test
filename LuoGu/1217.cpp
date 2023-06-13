#include <iostream>
#include <cstring>
using namespace std;
//只用枚举1，2，3，5，7位数 7：abcdcba
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
    int tot=0;
    int m[100000];
    int x,y;
    cin>>x>>y;
    for (int i = 1; i <= 9; i++)
    {
        if(isPrime(i)){
            m[++tot]=i;
        }
    }
    m[++tot]=11;
    for (int a = 1; a <= 9; a+=2)
    {
        for (int b = 0; b <= 9; b++)
        {
            if(isPrime(a*101+b*10)){//a*100+b*10+a简化
                m[++tot]=a*101+b*10;
            }
        }
        
    }
    for (int a = 1; a <= 9; a+=2)
    {
        for (int b = 0; b <= 9; b++)
        {
            for (int c = 0; c <= 9; c++)
            {
                if(isPrime(a*10001+b*1010+c*100)){
                    m[++tot]=a*10001+b*1010+c*100;
                }
            }
            
        }
        
    }
    for (int a = 1; a <= 9; a+=2)
    {
        for (int b = 0; b <= 9; b++)
        {
            for (int c = 0; c <= 9; c++)
            {
                for (int d = 0; d <= 9; d++)
                {
                    if(isPrime(a*1000001+b*100010+c*10100+d*1000)){
                        m[++tot]=a*1000001+b*100010+c*10100+d*1000;
                    }
                }
                
            }
            
        }
        
    }
    for (int i = 1; i <= tot; i++)
    {
        if(m[i]>=x&&m[i]<=y){
            cout<<m[i]<<endl;
        }
    }
    
    
    
}
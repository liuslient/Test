#include<iostream>
#include<cstring>
#include<math.h>
#include<string>
using namespace std;

int sum[100];
int main()
{
    int n;
    cin>>n;
    int num=n;
    int k=2;
    while (n>1)
    {
        if (n%k==0)
        {
            sum[k]++;
            n/=k;
            k=2;
        }
        else k++;
        
    }
    int flag=0;
    for (int i = 2; i <= num; i++)
    {
        if(sum[i]>0){
            if (sum[i]>1)
            {
                if(flag==0) cout<<i<<"^"<<sum[i];
                else cout<<"*"<<i<<"^"<<sum[i];
            }else{
                if(flag==0) cout<<i;
                else cout<<"*"<<i;
            }
            flag=1;
            
        }
    }
    
    
}
#include <iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
using namespace std;
int main()
{
    int i,j,n;
    cin>>n;
    string id[n+10],t;
    int year[n+10];
    int num[n+10];
    for ( i = 1; i <= n; i++)
    {
        cin>>id[i]>>year[i];
        num[i]=i;
    }
    for ( i = 1; i < n; i++)
    {
        for ( j = 1; j <= n-i;j++)
        {
            if (year[j]<60&&year[j+1]>=60 || year[j]>=60&&year[j+1]>=60&&year[j]<year[j+1] || year[j]>=60&&year[j]==year[j+1]&&num[j]>num[j+1] || year[j]<60&&year[j+1]<60&&num[j]>num[j+1])
            {
                swap(num[j],num[j+1]);
                t=id[j];
                id[j]=id[j+1];
                id[j+1]=t;
                swap(year[j],year[j+1]);
            }
            
        }
        
    }
    for ( i = 1; i <=n; i++)
    {
        cout<<id[i]<<endl;
    }
    

    
}
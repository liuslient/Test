#include<iostream>
using namespace std;
int main()
{
    int h[10];
    int shou;
    for (int i = 0; i < 10; i++)
    {
        cin>>h[i];
    }
    int cnt=0;
    cin>>shou;
    for (int i = 0; i < 10; i++)
    {
        if(h[i]<=shou+30){
            cnt++;
        }
    }
    cout<<cnt;
    
    
}

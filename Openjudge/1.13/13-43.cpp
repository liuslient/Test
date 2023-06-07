#include<bits/stdc++.h>
using namespace std;
int md[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main()
{
    int n,y,m1,m2,td,t;
    cin>>n;
    while(n--)
    {
        cin>>y>>m1>>m2;
        if(m1>m2)
            swap(m1,m2);
        if(y%400==0||y%100!=0&&y%4==0)
            md[2]=29;
        else
            md[2]=28;
        td=0;
        for (int i = m1; i < m2; i++)
        {
            td+=md[i];
        }
        if(td%7==0){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
        
    }
}

    
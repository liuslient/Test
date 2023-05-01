#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s1,s2;
    int i,n,a[100]={0};
    cin>>n;
    for ( i = 0; i < n; i++)
    {
        cin>>s1>>s2;
        if (s1==s2)
        {
            cout<<"Tie"<<endl;
        }
        else if (s1=="Scissors"&&s2=="Paper"||s1=="Rock"&&s2=="Scissors"||s1=="Paper"&&s2=="Rock")
        {
            cout<<"Player1"<<endl;
        }
        else
        {
            cout<<"Player2"<<endl;
        }
        
        
    }     
}
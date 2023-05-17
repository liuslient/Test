#include<iostream>
#include<string>
using namespace std;
int main()
{
    string a,b,c;
    int i,n;
    int tonga[200]={0};
    int tongb[200]={0};
    int duiying[200]={0};
    cin>>a>>b>>c;
    for ( i = 0; i < a.length(); i++)
    {
        if (duiying[a[i]]!=b[i]&&tongb[b[i]])
        {
            cout<<"Failed";
            return 0;
        }
        tonga[a[i]]++;
        tongb[b[i]]++;
        duiying[a[i]]=b[i];
    }
    for ( i ='A'; i <= 'Z'; i++)
    {
        if(tonga[i]*tongb[i]==0)
        {
            cout<<"Failed";
            return 0;
        }
    }
    for ( i = 0; i < c.length(); i++)
    {
        cout<<char(duiying[c[i]]);
    }
}
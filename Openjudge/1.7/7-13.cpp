#include<iostream>
#include<string>
using namespace std;
int main()
{
    string a;
    int i;
    getline(cin,a);
    for ( i = 0; i < a.length(); i++)
    {
        if (a[i]>='a'&&a[i]<='z')
        {
            a[i]-=32;
        }
        
    }
    cout<<a;
    
}
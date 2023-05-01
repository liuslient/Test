#include<iostream>
#include<string>
using namespace std;
int main()
{
    string a;
    int i,n,j;
    cin>>n;
    for ( j = 0; j < n; j++)
    {
        cin>>a;
        if (a[0]>='a'&&a[0]<='z')
        {
            a[0]-=32;
        }
        for ( i = 1; i < a.length(); i++)
        {
            if (a[i]>='A'&&a[i]<='Z')
            {
                a[i]+=32;
            }
        }
        cout<<a<<endl;
    }
    
}
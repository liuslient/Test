#include<iostream>
#include<cstring>
using namespace std;
int main()
{
    int n;
    cin>>n;
    n=n%26;
    char a[55];
    cin>>a;
    int la=strlen(a);
    for (int i = 0; i < la; i++)
    {
        a[i]-=26;
        a[i]+=n;
        if(a[i]<'a'){
            a[i]+=26;
        }
    }
    cout<<a;
    
}
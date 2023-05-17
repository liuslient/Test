#include<bits/stdc++.h>
using namespace std;

bool cmp(string x,string y)
{
    return x+y>y+x;
}

int main()
{
    int n,i;
    cin>>n;
    string a[n+10];
    for ( i = 1; i <=n; i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+n+1,cmp);
    for ( i = 1; i <=n; i++)
    {
        cout<<a[i];
    }
    
    

}
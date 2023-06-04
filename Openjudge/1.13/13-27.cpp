#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    string s1;
    int a[105];
    int r[100];
    cin>>s1;
    int len=s1.length();
    for (int i = 1; i <= len; i++)
    {
        a[i]=s1[i-1]-'0';
    }
    a[0]=len;
    int t=0;
    for (int i = 1; i <= a[0]; i++)
    {
        t=t*10+a[i];
        r[i]=t/13;
        t=t%13;
    }
    int k=1;
    while (k<a[0]&&r[k]==0)
    {
        k++;
    }
    for (int i = k; i <= a[0]; i++)
    {
        cout<<r[i];
    }
    cout<<endl<<t<<endl;
}
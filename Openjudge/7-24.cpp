#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int main()
{
    string a;
    int flag=0;
    getline(cin,a);
    int l=a.length();
    int tot=0;
    for(int i=0;i<l;i++)
    {
        if(a[i]!=' ')tot++;

        else
        {
            if(tot!=0)
            {
                cout<<tot<<",";
            }
            tot=0;
        }
        if(i==l-1)
            cout<<tot;

    }
    return 0;
}
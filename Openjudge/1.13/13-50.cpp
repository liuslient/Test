#include<bits/stdc++.h>
using namespace std;
int numRoot(int num)
{
    int nroot=0;
    while (num>0)
    {
        nroot+=num%10;
        num/=10;
    }
    while (nroot>9)
    {
        nroot=numRoot(nroot);
    }
    return nroot;
    
}
int main()
{
    string n;
    while (cin>>n)
    {
        int sum=0;
        for (int i = 0; i < n.length(); i++)
        {
            sum+=n[i]-'0';
        }
        cout<<numRoot(sum);
    }
    
}
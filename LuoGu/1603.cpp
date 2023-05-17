#include <iostream>
#include <cstring>
#include<algorithm>
using namespace std;

int main()
{
    string a[]={"one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen","twenty","a","both","another","first","second","third"};
    int b[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,1,2,1,1,2,3};
    int c[7],n,i,j;
    string t;
    for ( i = 1; i <=6; i++)
    {
        cin>>t;
        for ( j = 0; j < 26; j++)
        {
            if(t==a[j])
            {
                n++;
                c[n]=b[j];
                c[n]*=c[n];
                c[n]%=100;
            }
        }
        
    }
    sort(c+1,c+n+1);
    if (n==0)
    {
        cout<<0;
        return 0;
    }
    cout<<c[1];
    for ( i = 2; i <= n; i++)
    {
        if(c[i]<10)
        {
            cout<<0;
        }
        cout<<c[i];
    }
    
    
    
}
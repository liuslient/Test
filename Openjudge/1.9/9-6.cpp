#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;

bool isPrime(int n)
{
    int i,len=sqrt(n);
    for ( i = 2; i < len; i++)
    {
        if (n%i==0)
        {
            return false;
        }
        
    }
    return true;
    
}

int main()
{
    int i,maxn=0,minn=100,table[26]={0},n;
    string word;
    cin>>word;
    for ( i = 0; i < word.size(); i++)
    {
        table[word[i]-'a']++;
    }
    for ( i = 0; i < 26; i++)
    {
        if (table[i]>maxn)
        {
            maxn=table[i];
        }
        if (table[i]<minn&&table[i]!=0)
        {
            minn=table[i];
        }
    }
    n=maxn-minn;
    if (n>1&&isPrime(n))
    {
        cout<<"Lucky Word"<<endl;
        cout<<n<<endl;
    }
    else
    {
        cout<<"No Answer" << endl << "0" << endl;
    }
    
    
    
    
    
}
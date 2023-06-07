#include<bits/stdc++.h>
using namespace std;
struct book{
    int num;
    string name;
} a[1005];
int main()
{
    int m;
    cin>>m;
    for (int i = 0; i < m; i++)
    {
        cin>>a[i].num>>a[i].name;
    }
    string s;
    for (int i = 0; i < m; i++)
    {
        s+=a[i].name;
    }
    int z[26]={0},max;
    char ch;
    int len=s.length();
    int k=len;
    for (int i = 0; i < len; i++)
    {
        z[s[i]-'A']++;
    }
    max=z[0];
    len=0;
    for (int i = 0; i <= 25; i++)
    {
        if(z[i]>max){
            max=z[i];
            len=i;
        }
    }
    ch='A'+len;
    int flag=0;
    for (int i = 0; i < k; i++)
    {
        if(s[i]==ch)
        {
            flag++;
        }
    }
    cout<<ch<<endl;
    cout<<flag<<endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < a[i].name.length(); j++)
        {
            if(a[i].name[j]==ch)
            {
                cout<<a[i].num<<endl;
            }
        }
        
    }
    
    
    
    
    
    
}
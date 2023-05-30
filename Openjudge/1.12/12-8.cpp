#include<bits/stdc++.h>
using namespace std;

char mp[200][200];
int main()
{
    int d=0;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            mp[i][j]=(j+d)%26;
        }
        d++;
    }
    
    string k,c;
    cin>>k>>c;
    int lenk=k.size(),lenc=c.size();
    for (int i = 0; i < lenk; i++)
    {
        if(k[i]>='A'&&k[i]<='Z') k[i]+=32;
    }
    for (int i = 0; i < lenc; i++)
    {
        int j=i%lenk;
        char t=c[i];
        int lower=1;
        if(c[i]>='A'&&c[i]<='Z'){
            lower=0;
            t+=32;
        }
        if(c[i]>='A'&&c[i]<='Z') lower=0;
        for (int ii = 0; ii < 26; ii++)
        {
            if(mp[ii][k[j]-97]==t-97){
                if(lower) cout<<(char)(ii+97);
                else cout<<(char)(ii+65);
            }
        }
        
    }
    
    
    
}
#include<bits/stdc++.h>
using namespace std;
string a,b;
int i,t1[150],t2[150],p1[150],p2[150],len;
//明文中出现字母最多的次数 == 秘钥中最多的次数
//明文中次多的次数 == 秘钥中最多的次数
//用t1，t2统计秘钥和明文中每个字母出现次数；
//用p1,p2两个桶分别统计两个字符串中出现i(1,2,3,4…)次的字母种类的个数，
bool f(string a,string b)
{
    for ( i = 0; i < len; i++)
    {
        t1[a[i]]++;//字母出现次数
        t2[b[i]]++;
    }
    for ( i = 'A'; i <= 'Z'; i++)
    {
        p1[t1[i]]++;//
        p2[t2[i]]++;
    }
    for ( i = 1; i <= len; i++)
    {
        if(p1[i]!=p2[i]) return 0;
    }
    return 1;
    
    
    
}

int main()
{
    cin>>a>>b;
    len=a.size();
    if(f(a,b)) cout<<"YES";
    else cout<<"NO";
}
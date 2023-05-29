#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,c;
    char s;
    cin>>a>>s>>b;
    if(s=='+'){
        c=a+b;
    }
    if(s=='-'){
        c=a-b;
    }
    if(s=='*'){
        c=a*b;
    }
    if(s=='/'){
        c=a/b;
    }
    if(s=='%'){
        c=a%b;
    }
    cout<<c;
}
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,i,j;
    cin>>n;
    string s;
    cin>>s;
    int len=s.length();
    for ( i = 0; i < len; i++)
    {
        int t=i;
        while(s[i]==s[t]) ++t;
        if(t-i==n)
        {
            cout<<s[i];
            return 0;
        }
    }
    cout<<"No";
    
    
    
	
}
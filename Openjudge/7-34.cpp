#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
bool isPalin(string str)
{
    string s1(str);
    reverse(s1.begin(),s1.end());
    return str==s1;
}
int main()
{
    string s;
    cin>>s;
    int l,i,j;
    l=s.length();
    for ( j = 2; j <= l; ++j)
    {
        for ( i = 0; i <= l-j; ++i)
        {
            string sub=s.substr(i,j);
            if (isPalin(sub))
            {
                cout<<sub<<endl;
            }
            
        }
        
    }
    
}
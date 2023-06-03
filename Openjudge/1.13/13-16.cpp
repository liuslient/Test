#include <iostream>
#include <cstring>
using namespace std;
int main()
{
    int i,l,t,max_n=0,nim_n=100,mix1,mix2,min1,min2;
    string s;
    getline(cin,s);
    l=s.length();
    s[l]=' ';
    for ( i = 0; i <= l; i++)
    {
        if (s[i]!=' '&&s[i]!='.')
        {
            t++;
        }
        else if (t>0)
        {
            if (t>max_n)
            {
                max_n=t;
                mix1=i-t;
                mix2=i-1;
            }
            if (t<nim_n)
            {
                nim_n=t;
                min1=i-t;
                min2=i-1;
            }
            t=0;
            
            
        }
        
        
    }
    for ( i = mix1; i <= mix2; i++)
    {
        cout<<s[i];
    }

    
    
    
}
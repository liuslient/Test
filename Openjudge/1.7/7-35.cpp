#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int p1,p2,p3;
string s;
char first1,end1,f,p;
int i=0,j;
int main()
{
    cin>>p1>>p2>>p3;
    cin>>s;
    while(s[i])
    {
        first1=s[i-1];
        end1=s[i+1];
        f=s[i];
        if (f=='-'&&end1>first1&&(first1>='0'&&end1<='9'||first1>='a'&&end1<='z'))
        {
            for (p3 == 1?j=first1+1:j=end1-1;p3==1?j<end1:j>first1;p3==1?j++:j--)
            {
                p=j;
                if(p1==2)
                    p=(p>='a')?p-32:p;
                else if (p1==3) p='*';
                for (int k = 0; k < p2; k++)
                {
                    cout<<p;
                }
                
                
            }
            
        }
        else
            cout<<f;
        i++;
        
    }
}
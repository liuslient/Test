#include <iostream>
#include <cstring>
using namespace std;

int n,i,j,f[1005],maxx,len,z,d;
string s,x[1005],y;
int main()
{
    cin>>n>>s;
    len=s.size();
    for ( i = 0; i <= len-n; i++)
    {
        z++;
        x[z]=s.substr(i,n);
        for ( j = i; j <= len-n; j++)
        {
            y=s.substr(j,n);
            if(y==x[z]){
                f[z]++;
            }
        }
        if(f[z]>maxx){
            maxx=f[z];
        }
        
    }
    if(maxx>1){
        cout<<maxx<<endl;
        for ( i = 1; i <= z; i++)
        {
            if(f[i]==maxx){
                cout<<x[i]<<endl;
            }
        }
        
    }else{
        cout<<"NO";
    }
    
}
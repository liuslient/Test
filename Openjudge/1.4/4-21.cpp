#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
    int n,x,y,i;
    cin>>n>>x>>y;
    
    n-=y/x;
    if (y%x!=0)
    {
        n--;
    }
    if (n<0)
    {
        cout<<0;
        return 0;
    }
    
    cout<<n;
   

}



/*
int main()
{
    int n,x,y;
    cin>>n>>x>>y;
    cout<<n-ceil(1.0*y/x*1.0);
}
*/
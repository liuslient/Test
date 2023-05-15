#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;
int main()
{
    int n,i,j;
    cin>>n;
    string x,ans;
    for ( i = 1; i <=n; i++)
    {
        cin>>x;
        if(x.length()>ans.length()||x.length()==ans.length()&&x>ans)
        {
            ans=x;
            j=i;
        }
    }
    cout<<j<<endl<<ans;
}
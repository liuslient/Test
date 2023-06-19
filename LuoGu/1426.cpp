#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;

int main()
{
    double s,x,a=7,sum=0;
    cin>>s>>x;
    while(sum<=s+x){
        if(sum>=s-x&&sum+a<=s+x){
            cout<<'y';
            return 0;
        }
        sum+=a;
        a*=0.98;
    }
    cout<<'n';

    
}
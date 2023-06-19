#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;

int main()
{
    int n,a=1;
    cin>>n;
    while (n-a>0)//求第几趟
    {
        n-=a;
        a++;
    }
    if(a%2==0){
        cout<<n<<'/'<<a+1-n;
    }else{
        cout<<a+1-n<<'/'<<n;
    }
    

    
}
#include<iostream>
#include <iomanip>
using namespace std;
int main()
{
    double fei,sum=0;
    cin>>fei;
    if(fei<=150){
        sum=fei*0.4463;
    }
    else if(fei>150&&fei<=400){
        sum=(fei-150)*0.4663+150*0.4463;
    }
    else{
        sum=(fei-400)*0.5663+250*0.4663+150*0.4463;
    }
    cout<<fixed<<setprecision(1)<<sum;
}


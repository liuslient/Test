#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int main()
{
    string zu,hui;
    cin>>hui>>zu;
    int zu_sum=1,hui_sum=1;
    int len_zu,len_hui;
    len_zu=zu.length();
    len_hui=hui.length();
    for (int i = 0; i < len_hui; i++)
    {
        hui_sum*=((hui[i]-'A')+1);
    }
    for (int i = 0; i < len_zu; i++)
    {
        zu_sum*=((zu[i]-'A')+1);
    }
    if(zu_sum%47==hui_sum%47){
        cout<<"GO";
    }else{
        cout<<"STAY";
    }
    

}
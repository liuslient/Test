#include<iostream>
using namespace std;
//数字在计算机内存中都是以补码形式保存的
int main()
{
    string s;
    int n;
    cin>>n;
    for (int i = 1; i <= 32; i++)
    {
        s=char((n&1)+'0')+s;
        n>>=1;
    }
    cout<<s;
}
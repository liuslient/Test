#include<iostream>
#include<cstring>
#include<math.h>
#include<string>
using namespace std;
int main()
{
    int n;
    cin>>n;
    string word[n+5];
    for (int i = 0; i < n; i++)
    {
        cin>>word[i];
    }
    int len=word[0].size();
    cout<<word[0];
    for (int i = 1; i < n; i++)
    {
        if(len+1+word[i].size()<=80){
            cout<<" "<<word[i];
            len+=1+word[i].size();
        }else{
            cout<<endl;
            cout<<word[i];
            len=word[i].size();
        }
    }
    
    
}
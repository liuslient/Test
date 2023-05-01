#include<iostream>
#include<string>
using namespace std;
int main()
{
    string s1,s2;
    int i,n=0,s;
    float bi;
    cin>>bi;
    cin>>s1;
    cin>>s2;
    s=s1.length();
    /*
    换行符影响
    getline(cin,s1);
    getline(cin,s2);
    */
    for ( i = 0; i < s1.length(); i++)
    {
        if (s1[i]==s2[i])
        {
            n++;
        }
        
        
    }
    if (float(n)/s>=bi)
    {
        cout<<"yes";
    }
    else
        cout<<"no";
     
}
#include<bits/stdc++.h>
using namespace std;
bool isPrim(int n){
    for (int i = 2; i <=sqrt(n); i++)
    {
        if(n%i==0){
            return false;
        }
    }
    return true;
    
}
bool isPalindrom(string n){
    int len=n.size();
    for (int i = 0; i < len/2; i++)
    {
        if(n[i]!=n[len-1-i]){
            return false;
        }
    }
    return true;
    
}
int main()
{
    string n;
    int ans=0;
    cin>>n;
    int t=stoi(n);
    for (int i = 11; i <= t;i++)
    {
        if(isPrim(i)&&isPalindrom(to_string(i))){
            ans++;
        }
    }
    cout<<ans;
    
    
}
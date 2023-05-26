#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int main()
{
    char a[100][100];
    int n,i,j,len_s;
    string s;
    cin>>n>>s;
    len_s=s.length();
    int row=len_s/n;
    for ( j = 0; j < n; j++)
    {
        for ( i = 0; i < row; i++)
        {
            if (i%2==0)
            {
                cout<<s[i*n+j];
            }
            else
            {
                cout<<s[(i+1)*n-j-1];
            }
            
        }
        
    }
    
}
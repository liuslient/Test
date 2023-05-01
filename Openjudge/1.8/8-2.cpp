#include<iostream>
#include<string>
using namespace std;
int main()
{
    int n,i,j,row,po;
    cin>>n>>row>>po;
    for ( i = 1; i <= n; i++)
    {
        cout<<"("<<row<<","<<i<<") ";
    }
    cout<<endl;
    for ( i = 1; i <= n; i++)
    {
        cout<<"("<<i<<","<<po<<") ";
    }
    cout<<endl;
    for ( i = 1; i <= n; i++)
    {
        if (i+po-row>=1 && i+po-row<=n)
        {
            cout<<"("<<i<<","<<i+po-row<<") ";
        }
    }
    cout<<endl;
    for ( i = n; i >= 1; i--)
    {
        if (po+row-i>=1 && po+row-i<=n)
        {
            cout<<"("<<i<<","<<po+row-i<<") ";
        }
    }    
}
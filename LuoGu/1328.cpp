#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;

int main()
{
    int n,na,nb,i;
    int a_ans=0,b_ans=0;
    cin>>n>>na>>nb;
    int vs[5][5]={{0,0,1,1,0},{1,0,0,1,0},{0,1,0,0,1},{0,0,1,0,1},{1,1,0,0,0}};
    int a[na+10],b[nb+10];
    for (i= 0; i <na; i++)
    {
        cin>>a[i];
    }
    for ( i = 0; i < nb; i++)
    {
        cin>>b[i];
    }
    for ( i = 0; i < n; i++)
    {
        a_ans+=vs[a[i%na]][b[i%nb]];
        b_ans+=vs[b[i%nb]][a[i%na]];
    }
    cout<<a_ans<<" "<<b_ans;
    

}
#include<iostream>
using namespace std;
char a[1000000001];
int l;
int main()
{

    char c;
    scanf("%c",&c);
    while(c!='E')
    {

        a[l]=c;
        l++;
        scanf("%c",&c);
    }
    int p1=0,p2=0;
    for(int i=0;i<=l;i++)
    {

        if(a[i]=='W')
        p1++;
        else if(a[i]=='L')
        p2++;
        if(p1>=11&&(p1-p2>=2)||(p2>=11&&(p2-p1>=2)))
        {
            cout<<p1<<":"<<p2<<endl;
            p1=0;
            p2=0;
        }
    }
    cout<<p1<<":"<<p2<<endl;
    cout<<endl;
    p1=0;
    p2=0;
    for(int i=0;i<=l;i++)
    {

        if(a[i]=='W')
        p1++;
        else if(a[i]=='L')
        p2++;
        if(p1>=21&&(p1-p2>=2)||(p2>=21&&(p2-p1>=2)))
        {
            cout<<p1<<":"<<p2<<endl;
            p1=0;
            p2=0;
        }
    }
    cout<<p1<<":"<<p2<<endl;
    return 0;
}
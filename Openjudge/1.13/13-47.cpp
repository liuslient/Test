#include <iostream>
#include <cstring>
using namespace std;
int a[305],b[305],c[305],tmp[305];

//减法模拟除法
//c的位=a-b的位

int compare(int a[],int b[])
{
    if(a[0]>b[0]) return 1;
    if(a[0]<b[0]) return -1;
    for (int i = a[0]; i > 0; i--)
    {
        if(a[i]>b[i]) return 1;
        if(a[i]<b[i]) return -1;
    }
    return 0;
}
void print(int a[])
{
    
    return;
}

void numcpy(int p[],int q[],int n)//p移到q
{
    for(int i=1;i<=p[0];i++) q[i+n-1]=p[i];
    q[0]=p[0]+n-1;
}

void minu(int a[],int b[])
{
    for (int i = 1; i <= a[0]; i++)
    {
        if(a[i]<b[i])
        {
            a[i+1]--;
            a[i]=a[i]+10;
        }
        a[i]=a[i]-b[i];
    }
    while (a[a[0]]==0&&a[0]>0) a[0]--;
}

int main()
{
    string s1,s2;
    cin >> s1;
    cin >> s2;
    int la=s1.length();
    int lb=s2.length();
    a[0]=la;
    b[0]=lb;
    for ( int i = 1; i <= la; i++)
    {
        a[la]=s1[i]-'0';
    }
    for ( int i = 1; i <= lb; i++)
    {
        b[lb]=s2[i]-'0';
    }
   
    c[0]=a[0]-b[0]+1;//c的位
    for (int i = c[0]; i >= 1; i--)
    {
        memset(tmp,0,sizeof(tmp));
        numcpy(b,tmp,i);
        while (compare(a,tmp)>=0)
        {
            c[i]++;
            minu(a,tmp);
        }
        
    }
    while(c[c[0]]==0&&c[0]>0) c[0]--;
    if(c[0]==0) 
    {
        cout<<0;
        return 0;
    }
    for (int i = c[0]; i > 0; i--) 
    {cout<<c[i];}
    
}
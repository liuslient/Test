#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;

int main()
{
    string x,y;
    cin>>x>>y;
    int lenx=x.length();
    int leny=y.length();
    int tx,ty;
    for (int i = 0; i < lenx; i++)
    {
        if(x[i]=='.'){
            tx=i;
            break;
        }
    }
    for (int i = 0; i < leny; i++)
    {
        if(y[i]=='.'){
            ty=i;
            break;
        }
    }
    while (tx<ty)
    {
        x='0'+x;
        tx++;
        lenx++;
    }
    while (ty<tx)
    {
        y='0'+y;
        ty++;
        leny++;
    }
    while (lenx<leny)
    {
        x=x+'0';
        lenx++;
    }
    while (leny<lenx)
    {
        y=y+'0';
        leny++;
    }
    int len=x.length();
    int flag=0;
    //加法小数
    for (int i = len-1; i > tx; i--)
    {
        x[i]=x[i]-'0'+y[i];
        if(x[i]>'9'){
            x[i]=(x[i]-'0')%10+'0';
            if(i==tx+1)
                flag=1;
            else
            x[i-1]=x[i-1]+1;
        }
    }
    if(flag)
        x[tx-1]=x[tx-1]+1;
    //加法整数
    for (int i = tx-1; i > 0; i--)
    {
        x[i]=x[i]-'0'+y[i];
        if(x[i]>'9'){
            x[i]=(x[i]-'0')%10+'0';
            x[i-1]=x[i-1]+1;
        }
    }
    x[0]=x[0]-'0'+y[0];
    if(x[0]>'9')
    {
        x[0]=(x[0]-'0')%10+'0';
        x='1'+x;
    }
    int ans=lenx;
    for (int i = lenx-1; i >= 0; i--)
    {
        if(x[i]=='0'){
            ans=i;
        }else{
            break;
        }
    }
    for (int i = 0; i <ans; i++)
    {
        cout<<x[i];
    }
    
    
    

    
    
    
    
}
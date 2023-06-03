#include<iostream>
#include<cstring>
#include<math.h>
#include<string>
using namespace std;


int main()
{
    int y,m,d;
    scanf("%d-%d-%d",&y,&m,&d);
    int flag=1;
    if(m==1||m==3||m==5||m==7||m==8||m==10)
    {
        if(d>=31){
            d=1;
            m++;
            flag=0;
        }
        else
        {
            d++;
        }
    }
    if(m==12&&flag)
    {
        if(d>=31)
        {
            m=1;
            y++;
            d=1;
        }
        else
        {
            d++;
        }
    }
    if(m==2&&flag)
    {
        if((y%4==0&&y%100!=0)||y%400==0)
        {
            if (d>=29)
            {
                d=1;
                m++;
            }
            else{
                d++;
            }
            
        }
        else{
            if (d>=28)
            {
                d=1;
                m++;
            }
            else{
                d++;
            }
        }
    }
    if((m==4||m==6||m==9||m==11)&&flag)
    {
        if(d>=30){
            d=1;
            m++;
        }
        else
        {
            d++;
        }
    }
    printf("%d-%02d-%02d",y,m,d);

    
    
}
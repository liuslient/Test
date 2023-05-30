#include <iostream>
#include <cstring>
using namespace std;


#include<iostream>
#include<cstring>
using namespace std;
int mons[2][13]=
{
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int isrun(int y){
    if(y%4==0&&y%100!=0||y%400==0)
    {
        return 1;
    }
    return 0;
}

int years[2]={365,366};

int main()
{
    int n,hour,minit,sec,day,mon,year,mhor,mmin,msec,mday,mmon,myear;
    cin>>n;
    while (n--)
    {
        scanf("%d:%d:%d %d.%d.%d",&hour,&minit,&sec,&day,&mon,&year);
        int secs,days=0;
        secs=sec+60*minit+3600*hour;
        for (int i = 2000; i < year; i++)
        {
            days+=years[isrun(i)];
        }
        for (int i = 1; i < mon; i++)
        {
            days+=mons[isrun(year)][i];
        }
        days+=day-1;
        myear=days/1000;
        days%=1000;
        mmon=days/100+1;
        days%=100;
        mday=days+1;
        secs=secs*125/108;
        mhor=secs/10000;
        secs%=10000;
        mmin=secs/100;
        msec=secs%100;
        printf("%d:%d:%d %d.%d.%d\n",mhor,mmin,msec,mday,mmon,myear);     
        
    }
    
}
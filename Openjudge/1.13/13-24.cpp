#include<iostream>
#include<cstring>
#include<math.h>
#include<string>
using namespace std;
bool isrun(int x){
    if ((x%4==0&&x%100!=0)||x%400==0)
    {
        return 1;
    }
    return 0;
}

int main()
{
    int year,month;
    cin>>year>>month;
    printf("Sun Mon Tue Wed Thu Fri Sat\n");
    int a[]={31,28,31,30,31,30,31,31,30,31,30,31};
    int day=0;
    for (int i = 1900; i < year; i++)
    {
        if(isrun(year)){
            day+=366;
        }else{
            day+=365;
        }
    }
    if(isrun(year)) a[1]=29;
    for (int i = 0; i < month-1; i++)
    {
        day+=a[i];
    }
    int ans;
    if(day%7==0) ans=1;
    else{
        ans=day%7+1;
    }
    int temp=a[month-1];
    for (int i = 0; i < ans%7; i++)
    {
        printf("    ");
    }
    int cnt=1;
    while (temp)
    {
        int res=ans%7+cnt;
        if(res%7==0)
        {
            printf("%3d\n",cnt);
        }else{
            printf("%3d ",cnt);
        }
        cnt++;
        temp--;
    }
    
    
    
    
}
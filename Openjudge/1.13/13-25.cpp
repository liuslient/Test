/*
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
    int startYear,startMonth,startDay,endYear,endMonth,endDay;
    cin>>startYear>>startMonth>>startDay;
    cin>>endYear>>endMonth>>endDay;
    int a[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    int day=0,start_day=0;
    for (int i = startYear+1; i < endYear; i++)
    {
        if(isrun(i)){
            day+=366;
        }else{
            day+=365;
        }
    }
    if(isrun(startYear)) a[2]=29;
    for (int i = 1; i < startMonth; i++)
    {
        start_day=start_day+a[i];
    }
    if (isrun(startYear))
    {
        start_day=366-start_day;
    }else{
        start_day=365-start_day;
    }
    day+=start_day;
    day+=startDay;
    for (int i = 1; i < endMonth; i++)
    {
        day+=a[i];
    }
    day+=endDay;
    cout<<day-2;   
}
*/
#include <iostream>
#include <cstdio>
using namespace std;
int monthdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
bool isrun(int year);
int getDays(int year,int month,int day);
int main()
{
	int startYear, startMonth, startDay, endYear, endMonth, endDay, days;
	cin>>startYear>>startMonth>>startDay;
    cin>>endYear>>endMonth>>endDay;
	days = getDays(endYear, endMonth, endDay)-getDays(startYear, startMonth, startDay);
	printf("%d",days);
}
bool isrun(int year)
{
	if(year%4==0 && (year%100!=0 || year%400==0))
	{
		return true;
	}
	return false;
}
int getDays(int year,int month,int day)
{
	int days=0;
	for(int i=1;i<year;i++)
		{
			if(isrun(i))
			{
				days += 366;
			}else
			{
				days += 365;
			}
		}
		for(int i=1;i<month;i++)
		{
			days+=monthdays[i-1];
		}
		if(month > 2 && isrun(year))
		{
			days++;
		}
		days += day;
	return days;
}

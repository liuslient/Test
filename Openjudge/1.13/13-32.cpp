#include<bits/stdc++.h>
using namespace std;
int md[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
string ds[]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

bool isrun(int n){
    if((n%4==0&&n%100!=0)||n%400==0){
        return 1;
    }
    return 0;
}
int getday(int n){
    return isrun(n)?366:365;
}
int main()
{
    int td,y=2000,m=1,d=1,day=6;
    cin>>td;
    day=(day+td)%7;
    while (td>=getday(y))
    {
        td-=getday(y);
        ++y;
    }
    md[2]=isrun(y)?29:28;
    while (td>=md[m])
    {
        td-=md[m];
        m++;
    }
    d+=td;
    printf("%d-%02d-%02d",y,m,d);
    cout<<" "<<ds[day];
    
    
    

}
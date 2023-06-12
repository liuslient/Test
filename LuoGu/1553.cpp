#include<iostream>
#include<cstring>
using namespace std;
int main()
{
    char a[30];
    cin>>a;
    int la=strlen(a),p=la,flag;
    for (int i = 0; i < la; i++)
    {
        if(a[i]=='.'||a[i]=='%'||a[i]=='/'){
            p=i;
        }
    }
    flag=1;
    for (int i = p-1; i >= 0; i--)
    {
        if(a[i]=='0'&&flag==1&&i>0)
            continue;
        flag=0;//去除前导0
        cout<<a[i];
    }
    if(p!=la){
        cout<<a[p];
        if(a[p]=='/'){
            flag=1;
            for (int i = la-1; i >= p+1; i--)
            {
                if(a[i]=='0'&&flag==1&&i>p+1)
                    continue;
                flag=0;//去除前导0
                cout<<a[i];
            }
        }
        if(a[p]=='.'){
            int temp=p+1;
            while(a[temp]=='0'&&temp<la-1)
                temp++;
            for (int i = la-1; i >= temp; i--)
            {
                cout<<a[i];
            }
        }
    }
    
    
    
}
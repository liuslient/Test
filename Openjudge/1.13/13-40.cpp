#include<bits/stdc++.h>
using namespace std;
int main()
{
    char s[305];
    scanf("%s",s);
    bool isNum=false;
    int len=strlen(s),num=0,a[305],an=0;
    for (int i = 0; i <= len; i++)
    {
        if(s[i]>='0'&&s[i]<='9'){
            isNum=true;
            num=num*10+s[i]-'0';
        }
        else if(isNum)
        {
            a[++an]=num;
            isNum=false;
            num=0;
        }
        
    }
    
    
    if(an==0)
        printf("0");
    else{
        for (int i = 1; i <= an-1; i++)
        {
            for (int j = 1; j <= an-i; j++)
            {
                if(a[j]>a[j+1]){
                    swap(a[j],a[j+1]);
                }
            }
            
        }
        printf("%d",a[1]);
        for (int i = 2; i <= an; i++)
        {
            printf(",%d",a[i]);
        }
        
        
    }
    
}
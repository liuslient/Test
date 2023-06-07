#include<bits/stdc++.h>
using namespace std;
char x[10000];
int y[10000],z[10000];
int a,b,c,e,d,n;
int chu()
{
    int yu1=0,yu2=0;
    for(int i=0;i<c;i++){
        yu1=(y[i]+yu2*a)%b;
        y[i]=(y[i]+yu2*a)/b;
        yu2=yu1;
    }
    return yu1;
}
int main()
{
    cin>>n;
    while (n)
    {
        n--;
        memset(x,0,sizeof(x));
        memset(y,0,sizeof(y));
        memset(z,0,sizeof(z));
        scanf("%d",&a);
        getchar();
        for (int i = 0; ; i++)
        {
            scanf("%c",&x[i]);
            if(x[i]==','){
                x[i]=0;
                break;
            }if(x[i]>='0'&&x[i]<='9'){
                y[i]=x[i]-'0';
            }else{
                y[i]=x[i]-'A'+10;
            }
        }
        scanf("%d",&b);
        c=strlen(x);
        for ( e = 0,d=1; ; e++,d=1)
        {
            z[e]=chu();
            for (int i = 0; i < c; i++)
            {
                if(y[i]!=0){
                    d=0;
                    break;
                }
            }
            if(d==1)
            {
                break;
            }
            
        }
        while(e>=0){
            if(z[e]>=0&&z[e]<=9)
                cout<<z[e];
            else
                printf("%c",z[e]-10+'A');
            e--;
        }
        cout<<endl;
        
        
    }
    
}
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

string haab[19]={"pop","no","zip","zotz","tzec","xul","yoxkin","mol","chen","yax","zac","ceh","mac", 
	"kankin","muan","pax","koyab","cumhu","uayet"};
string holly[20]={"imix","ik","akbal","kan","chicchan","cimi","manik","lamat","muluk","ok","chuen","eb",  "ben","ix","mem","cib","caban","eznab","canac","ahau"};
int hollynum[260];
string hollyname[260];
typedef long long ll;

void intt()
{
    int k=1,g=0;
    for (int i = 1; i <= 260; i++)
    {
        hollynum[i-1]=k;
        hollyname[i-1]=holly[g];
        k++;
        if(k>13){
            k=1;
        }
        g++;
        if(g>=20){
            g=0;
        }
    }
    
}

int main()
{
    intt();
    int n;
    cin>>n;
    int year,date;
    char months[10];
    ll month,days;
    cout<<n<<endl;
    while(n--)
    {
        scanf("%d.%s%d",&date,months,&year);
        for (int j = 0; j < 19; j++)
        {
            if(haab[j]==months)
            {
                month=j+1;
            }
        }
        days=year*365;
        days+=(month-1)*20;
        days+=date;
        ll w=days/260;
        ll d=days%260;
        cout<<hollynum[d]<<" "<<hollyname[d]<<" "<<w<<endl;
        days=0;
        
    }
}
/*
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int main()
{
    int n,i,j;
    cin>>n;
    int mo[n+10],ban[n+10],lun[n+10],money[n+10]={0},sum=0,max;
    string name[n+10];
    char gan[n+10],xi[n+10];
    for ( i = 1; i <= n; i++)
    {
        cin>>name[i]>>mo[i]>>ban[i]>>gan[i]>>xi[i]>>lun[i];
    }
    for ( i = 1; i <=n; i++)
    {
        if (ban[i]>80&&gan[i]=='Y')
        {
            money[i]+=850;
        }
        if (mo[i]>85&&xi[i]=='Y')
        {
            money[i]+=1000;
        }
        if (mo[i]>90)
        {
            money[i]+=2000;
        }
        if (mo[i]>85&&ban[i]>80)
        {
            money[i]+=4000;
        }
        if (mo[i]>80&lun[i]>=1)
        {
            money[i]+=8000;
        }
        
    }
    max=money[1];
    for ( i = 1; i <= n; i++)
    {
        sum+=money[i];
        if (money[i]>=max)
        {
            max=money[i];
        }
        
    }
    for ( i = 1; i <= n; i++)
    {
        if (money[i]==max)
        {
            cout<<name[i]<<endl<<money[i]<<endl<<sum;
        }
        
    }
    
    
}
*/

#include<iostream>
#include<cstring>
#include<string>
using namespace std;
typedef struct applicant{
	string name;
	int scoreInStudy;
	int scoreInClass;
	char isClassLeader;
	char isfromWest;
	int numOfPaper;
}; 
int main(){
	int n;
	cin>>n;
	applicant students[n+5];
	for(int i=1;i<=n;i++){
		cin>>students[i].name>>students[i].scoreInStudy>>students[i].scoreInClass;
		cin>>students[i].isClassLeader>>students[i].isfromWest>>students[i].numOfPaper;
	}
	
	int totalMoney[n+5];
	memset(totalMoney,0,sizeof(totalMoney));

	for(int i=1;i<=n;i++){
		if(students[i].scoreInStudy>80&&students[i].numOfPaper>=1)
		totalMoney[i]+=8000; 
	}
	for(int i=1;i<=n;i++){
		if(students[i].scoreInStudy>85&&students[i].scoreInClass>80)
		totalMoney[i]+=4000; 
	}
	for(int i=1;i<=n;i++){
		if(students[i].scoreInStudy>90)
		totalMoney[i]+=2000; 
	}
	for(int i=1;i<=n;i++){
		if(students[i].scoreInStudy>85&&students[i].isfromWest=='Y')
		totalMoney[i]+=1000; 
	}
	for(int i=1;i<=n;i++){
		if(students[i].scoreInClass>80&&students[i].isClassLeader=='Y')
		totalMoney[i]+=850; 
	}
	
	
	int max=totalMoney[1];
	int No=1;   
	int sum=totalMoney[1];                     
	for(int i=2;i<=n;i++){
		if(totalMoney[i]>max){
			max=totalMoney[i];
			No=i;
		}
		sum+=totalMoney[i];
	}
	
	cout<<students[No].name<<endl;
	cout<<max<<endl;
	cout<<sum;
	return 0;
} 

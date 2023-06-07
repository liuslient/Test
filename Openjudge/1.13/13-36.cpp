#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
int two[30];
int a,b;
int zhuan(int t)
{
    memset(two,0,sizeof(two));
    int size=0;
    do
    {
        two[size++]=t%2;
        t/=2;
    } while (t!=0);
    return size;
}
int main()
{
    int countA=0,countB=0;
    for (int i = 1; i <=1000; i++)
    {
        int count1=0;
        int size=zhuan(i);
        for (int j = 0; j < size; j++)
        {
            if(two[j]==1)
            {
                count1++;
            }
        }
        int count0=size-count1;
        if(count1>count0){
            countA++;
        }else{
            countB++;
        }
        
    }
    printf("%d %d",countA,countB);
    
}
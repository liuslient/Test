#include<stdio.h>
#include<math.h>
#define N 100001
int main()
{
    int i,n,na,nb,a[N],b[N],win=0;
    scanf("%d %d %d",&n,&na,&nb);
    for ( i = 0; i < na; i++)
    {
        scanf("%d",&a[i]);
    }
    for ( i = na; i < n; i++)
    {
        a[i]=a[i%na];
    }
    for ( i = 0; i < nb; i++)
    {
        scanf("%d",&b[i]);
    }
    for ( i = nb; i < n; i++)
    {
        b[i]=b[i%nb];
    }
    for ( i = 0; i < n; i++)
    {
        if ((a[i]==0&&b[i]==2) ||
            (a[i]==2&&b[i]==5) ||
            (a[i]==5&&b[i]==0))
            win++;
        if ((b[i]==0&&a[i]==2) ||
            (b[i]==2&&a[i]==5) ||
            (b[i]==5&&a[i]==0))
            win--;
    }
    if (win>0)
    {
        printf("A");
    }
    if(win<0)
    {
        printf("B");
    }
    if (win==0)
    {
        printf("draw");
    }
    
        
    

}
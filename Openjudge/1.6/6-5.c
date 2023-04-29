#include<stdio.h>
int main()
{
    int n,i,a[100];
    double xiao=0,zhong=0,da=0,lao=0;
    scanf("%d",&n);
    for ( i = 0; i < n; i++)
    {
        scanf("%d",&a[i]);
    }
    for ( i = 0; i < n; i++)
    {
        if (a[i]<=18)
        {
            xiao++;
        }
        else if (a[i]>18&&a[i]<36)
        {
            zhong++;
        }
        else if (a[i]>35&&a[i]<61)
        {
            da++;
        }
        else
        {
            lao++;
        }
    }
    printf("%.2f%%\n%.2f%%\n%.2f%%\n%.2f%%\n",100.0*xiao/n,100.0*zhong/n,100.0*da/n,100.0*lao/n);
    
    
}